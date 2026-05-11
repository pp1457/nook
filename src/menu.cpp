#include "menu.hpp"

#include <ctime>

#include <vector>
#include <string>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/mouse.hpp" 
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "colors.hpp"
#include "time_utils.hpp"


using namespace ftxui;

std::vector<std::string> GetDisplayNames(std::vector<Entry> entries) {
  std::vector<std::string> display_names;

  for (auto entry: entries) {
    std::tm tm = *std::localtime(&entry.create_time);
    std::string title = entry.title.substr(0, 65) + (entry.title.size() > 65 ? "..." : "");
    display_names.push_back(std::format("{:<25} {}", display_date(tm), title));
  }

  return display_names;
}


Component GetRecentlyMenu(std::vector<std::string>* entries, int* selected) {
  auto option = MenuOption::Vertical();

  option.entries_option.transform = [](EntryState state) {
    state.label = (state.active ? "> " : "  ") + state.label;
    Element e = text(state.label);
    if (state.active) {
      e = e | color(header_color) | bold;
    } else {
      e = e | color(dim_color);
    }
    return e;
  };

  return Menu(entries, selected, option);
}

