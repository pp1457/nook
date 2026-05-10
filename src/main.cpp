#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <format>
#include <optional>

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/screen/screen.hpp"

#include "home_screen.hpp"
#include "vim_config.hpp"
#include "entry.hpp"
#include "menu.hpp"
#include "colors.hpp"
                                    
using namespace ftxui;
namespace fs = std::filesystem;

void OpenInVim(ScreenInteractive& screen, fs::path entry_path, fs::path vimrc_path, EntryList& entry_list) {

    std::string command  = std::format(
        "vim -u '{}' '{}'",
        vimrc_path.string(),
        entry_path.string()
    ); 

    screen.WithRestoredIO([&command] {
      std::cout << "\033]11;#1c1612\007" << std::flush;
      std::cout << "\033[2J\033[H" << std::flush;
      std::system(command.c_str());
      std::cout << "\033]111\007" << std::flush;
    })();

    if (fs::exists(entry_path) && fs::file_size(entry_path) == 0) {
      fs::remove(entry_path);
    }

    entry_list.UpdateEntry(entry_path);
}

int main() {
  const char* home = std::getenv("HOME");
  if (!home) return 1;

  fs::path nook_dir = fs::path(home) / ".nook";
  fs::path entry_dir = nook_dir / "entries";
  fs::path config_dir = nook_dir / "config";
  fs::path vimrc_path = config_dir / "vimrc";

  fs::create_directories(nook_dir);
  fs::create_directories(entry_dir);
  fs::create_directories(config_dir);
  EnsureVimrcExists(config_dir);

  EntryList entry_list{entry_dir};

  auto screen = ScreenInteractive::Fullscreen();

  int selected = 0;
  auto entries = entry_list.GetSortedEntries();
  auto display_names = GetDisplayNames(entries);
  auto recently_menu = GetRecentlyMenu(&display_names, &selected);


  auto component = Renderer(recently_menu, [&] { 

      auto recently_section = entries.empty()
        ? text("empty brain...") | color(dim_color)
        : recently_menu->Render() | frame | size(HEIGHT, LESS_THAN, 10);

      return home_screen(recently_section);
  });

  auto with_keys = CatchEvent(component, [&](Event event) {

    if (event == Event::Character('q')) {
      screen.Exit();
      return true; 
    } 

    if (event == Event::Character('n')) {
      auto now_time_t = std::time(nullptr);
      std::tm tm = *std::localtime(&now_time_t);
      std::string timestamp = std::format(
          "{:04}-{:02}-{:02}-{:02}{:02}{:02}",
          tm.tm_year + 1900,
          tm.tm_mon + 1,
          tm.tm_mday,
          tm.tm_hour,
          tm.tm_min,
          tm.tm_sec
      );

      fs::create_directories(entry_dir);
      fs::path entry_path = entry_dir / (timestamp + ".txt");

      OpenInVim(screen, entry_path, vimrc_path, entry_list);

    } else if (event == Event::Return) {

      fs::path entry_path = entries[selected].path;
      OpenInVim(screen, entry_path, vimrc_path, entry_list);

    } else {
      return false;
    }

    entries = entry_list.GetSortedEntries();
    display_names = GetDisplayNames(entry_list.GetSortedEntries());

    if (selected >= (int)display_names.size()) {
      selected = std::max(0, (int)display_names.size() - 1);
    }

    return true;
  });

  screen.Loop(with_keys);

  return 0;
}
