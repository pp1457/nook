#include <string>    // for string, operator+

#include "ftxui/dom/elements.hpp"   // for text, Element, border, center
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/screen/screen.hpp"  // for Screen
                                    
using namespace ftxui;

const auto title_color   = Color::RGB(220, 170, 110);
const auto header_color  = Color::RGB(200, 150, 100);
const auto body_color    = Color::RGB(220, 200, 170);
const auto dim_color     = Color::RGB(140, 125, 105);
const auto bg_color      = Color::RGB(28, 22, 18);

Element title(const std::string& s) { return text(s) | bold | color(title_color); }
Element header(const std::string& s) { return text(s) | bold | color(header_color); }


int main() {


  auto screen = ScreenInteractive::Fullscreen();

  auto component = Renderer([] {
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
              text("Tuesday, May 8 · 47 entries · last visit 2 days ago") | color(dim_color)
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
      }) | bgcolor(bg_color)   // warm dark
          | flex;;
  });

  auto with_keys = CatchEvent(component, [&](Event event) {
      if (event == Event::Character('q')) {
          screen.Exit();
          return true;  // event was handled
      }
      return false;  // event was not handled, pass it on
  });

  screen.Loop(with_keys);

  return 0;
}
