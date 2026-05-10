#pragma once

#include "ftxui/dom/elements.hpp"

using namespace ftxui;

const auto title_color   = Color::RGB(220, 170, 110);
const auto header_color  = Color::RGB(200, 150, 100);
const auto body_color    = Color::RGB(220, 200, 170);
const auto dim_color     = Color::RGB(140, 125, 105);
const auto bg_color      = Color::RGB(28, 22, 18);

inline Element title(const std::string& s) { return text(s) | bold | color(title_color); }
inline Element header(const std::string& s) { return text(s) | bold | color(header_color); }

