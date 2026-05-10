#include "home_screen.hpp"

#include <filesystem>
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

#include "colors.hpp"
#include "entry.hpp"
#include "time_utils.hpp"
                                    
using namespace ftxui;

Element home_screen(Element recently_section) {

  auto now_time_t = std::time(nullptr);
  std::tm tm = *std::localtime(&now_time_t);

  return hbox({
    text("    "),
    vbox({
      hbox({
        text("nook") | bold | color(title_color),
        text(", a quiet place") | color(dim_color),
      }),
      separator() | color(dim_color),
      vbox({
        text(""),
        text(greeting(tm) + display_date(tm)) | color(dim_color)
      }),
      text(""),
      text(""),
      header("recently"),
      text(""),
      hbox({
        text("    "),
        recently_section 
      }),
      text(""),
      text(""),
      header("open questions"),
      text(""),
      hbox({
        text("    "),
        vbox({
          text("Coming Soon"),
        }) | color(dim_color)
      }),
      text(""),
      text(""),
      header("topics"),
      text(""),
      hbox({
        text("    "),
        vbox({
          text("Coming Soon"),
        }) | color(dim_color)
      }),
      filler(),
      separator() | color(dim_color),
      hbox({
        text("n") | bold | color(title_color),    // letter pops in amber
        text("  new      ") | color(dim_color),
        text("b") | bold | color(title_color),
        text("  browse      ") | color(dim_color),
        text("/") | bold | color(title_color),
        text("  search      ") | color(dim_color),
        text("q") | bold | color(title_color),
        text("  leave") | color(dim_color),
      }),
      text("")
    }) | flex,
    text("    ")
  }) | bgcolor(bg_color) | flex;
}
