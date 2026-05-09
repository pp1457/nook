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
                                    
using namespace ftxui;
namespace fs = std::filesystem;

int main() {
  const char* home = std::getenv("HOME");
  if (!home) return 1;

  fs::path nook_dir = fs::path(home) / ".nook";

  EnsureConfigExists(nook_dir);

  auto screen = ScreenInteractive::Fullscreen();

  auto component = Renderer([] { return home_screen(); });

  auto with_keys = CatchEvent(component, [&](Event event) {
    if (event == Event::Character('q')) {
      screen.Exit();
      return true; 

    } else if (event == Event::Character('n')) {

      std::optional<fs::path> p = CreateNewEntry(nook_dir);
      if (!p) return true;

      fs::path entry_path = *p;
      fs::path vimrc_path = nook_dir / "config" / "vimrc";
      std::string command  = std::format(
        "vim -u '{}' '{}'",
        vimrc_path.string(),
        entry_path.string()); 

      screen.WithRestoredIO([&command] {
        std::cout << "\033]11;#1c1612\007" << std::flush;
        
        std::cout << "\033[2J\033[H" << std::flush;
        
        std::system(command.c_str());
        
        std::cout << "\033]111\007" << std::flush;
      })();
      return true; 
    } else {
      return false;
    }
  });

  screen.Loop(with_keys);

  return 0;
}
