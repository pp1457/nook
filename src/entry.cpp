#include "entry.hpp"

#include <ctime>

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <format>
#include <optional>

                                    
namespace fs = std::filesystem;

EntryList::EntryList(fs::path entry_dir): entry_dir_(entry_dir) {
  fs::create_directories(entry_dir);
  Refresh();
}

void EntryList::UpdateEntry(fs::path target_entry_path) {
  auto p = LoadEntry(target_entry_path);
  bool exist = p ? true : false;

  if (!exist) {
    std::erase_if(all_entries_, [&](const Entry& e) {
        return e.path == target_entry_path;
    });
    return;
  } 

  Entry target_entry = *p;

  for (auto& entry: all_entries_) {
    if (entry.path == target_entry_path) {
      entry = target_entry;
      return;
    }
  }

  all_entries_.push_back(target_entry);
}

std::optional<Entry> EntryList::LoadEntry(fs::path entry_path) {

  Entry entry;

  entry.path = entry_path;

  if (fs::exists(entry_path) == false) {
    return std::nullopt;
  }

  auto file_time = fs::last_write_time(entry_path);
  auto sys_time = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
      file_time - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
  );
  entry.edit_time = std::chrono::system_clock::to_time_t(sys_time);

  try {
    std::string stem = entry_path.stem().string();
    std::tm tm = {};
    tm.tm_year = std::stoi(stem.substr(0, 4)) - 1900;
    tm.tm_mon  = std::stoi(stem.substr(5, 2)) - 1;
    tm.tm_mday = std::stoi(stem.substr(8, 2));
    tm.tm_hour = std::stoi(stem.substr(11, 2));
    tm.tm_min  = std::stoi(stem.substr(13, 2));
    tm.tm_sec  = std::stoi(stem.substr(15, 2));
    tm.tm_isdst = -1;
    entry.create_time = std::mktime(&tm);
  } catch (const std::exception&) {
    return std::nullopt;
  }

  std::ifstream f(entry_path);
  std::getline(f, entry.title);

  return entry;
}

void EntryList::Refresh() {
  all_entries_.clear();
  for (const auto& dir_entry: fs::directory_iterator(entry_dir_)) {
    UpdateEntry(dir_entry.path());
  }
}

std::vector<Entry> EntryList::GetSortedEntries() {
  sort(all_entries_.begin(), all_entries_.end(), [&](const auto& lhs, const auto& rhs) {
      if (lhs.edit_time != rhs.edit_time)
        return lhs.edit_time > rhs.edit_time;
      return lhs.create_time > rhs.create_time;
  });
  return all_entries_;
}
