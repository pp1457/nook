#include <filesystem>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <format>
#include <optional>

#include "ftxui/dom/elements.hpp"

#include "entry.hpp"
                                    
using namespace ftxui;
namespace fs = std::filesystem;

std::optional<fs::path> CreateNewEntry(fs::path nook_dir) {

  auto now_time_t = std::time(nullptr);
  std::tm tm = *std::localtime(&now_time_t);
  std::string timestamp = std::format(
    "{:04}-{:02}-{:02}-{:02}{:02}{:02}",
    tm.tm_year + 1900,
    tm.tm_mon + 1,
    tm.tm_mday,
    tm.tm_hour,
    tm.tm_min,
    tm.tm_sec);

  fs::path entries_dir = nook_dir / "entries";
  
  fs::create_directories(entries_dir);

  fs::path entry_path = entries_dir / (timestamp + ".txt");

  return entry_path;
}
