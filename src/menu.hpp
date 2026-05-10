#pragma once

#include <vector>
#include <string>

#include "ftxui/component/component.hpp"

#include "entry.hpp"

std::vector<std::string> GetDisplayNames(std::vector<Entry> entries);
ftxui::Component GetRecentlyMenu(std::vector<std::string>* entries, int* selected);
