#pragma once

#include <filesystem>
#include <vector>
#include <ctime>
#include <string>
#include <optional>
                                    
struct Entry {
  std::filesystem::path path;
  std::string title;
  std::time_t create_time;
  std::time_t edit_time;
};

class EntryList {

public:
  explicit EntryList(std::filesystem::path entry_dir);
  void UpdateEntry(std::filesystem::path target_entry_path);
  std::vector<Entry> GetSortedEntries();

private:
  std::filesystem::path entry_dir_;
  std::vector<Entry> all_entries_;
  void Refresh();
  std::optional<Entry> LoadEntry(std::filesystem::path entry_path);

};
