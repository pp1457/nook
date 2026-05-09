#include "home_screen.hpp"
#include "colors.hpp"

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
                                    
using namespace ftxui;

std::string greeting(std::tm tm) {
  int hour = tm.tm_hour;
  if (hour < 5)   return "still up";
  if (hour < 12)  return "good morning";
  if (hour < 19)  return "good afternoon";
  if (hour < 23)  return "good evening";
  return "late night";
}

std::string status_line() {

  auto now_time_t = std::time(nullptr);
  std::tm tm = *std::localtime(&now_time_t);

  const char* day_names[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
  };

  const char* month_names[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  return std::format("{} · {} · {} {}",
    greeting(tm), 
    day_names[tm.tm_wday], 
    month_names[tm.tm_mon], 
    tm.tm_mday); 
}

Element home_screen() {
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
        text(status_line()) | color(dim_color)
      }),
      text(""),
      text(""),
      header("recently"),
      text(""),
      hbox({
        text("    "),
        vbox({
          text("Mon May  6    thinking about SPSC queues and false sharing"),
          text("Sat May  3    ASC26 — bandwidth or compute first?"),
          text("Fri May  2    why my ringbuffer corrupts at high contention"),
          text("Wed Apr 30    reading: art of multiprocessor programming"),
          text("Mon Apr 28    what is \"memory ordering\" actually doing?")
        }) | color(dim_color)
      }),
      text(""),
      text(""),
      header("open questions"),
      text(""),
      hbox({
        text("    "),
        vbox({
          text("Mon May  6    why does SPSC throughput tank past 8 cores?"),
          text("Sat May  3    is alignas(64) enough on ARM, or do I need 128?"),
          text("Fri May  2    when is hazard pointer overhead actually worth paying?"),
          text("Wed Apr 30    how does the kernel pick between RCU and seqlock?"),
          text("Mon Apr 28    why is my benchmark 3x slower with -O3 than -O2?"),
        }) | color(dim_color)
      }),
      text(""),
      text(""),
      header("topics"),
      text(""),
      hbox({
        text("    "),
        vbox({
          text("concurrency           12 entries · most recent 2 days ago"),
          text("asc26                  8 entries · most recent 5 days ago"),
          text("memory ordering        6 entries · most recent 1 week ago"),
          text("debugging             11 entries · most recent yesterday"),
          text("performance            9 entries · most recent 3 days ago"),
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
