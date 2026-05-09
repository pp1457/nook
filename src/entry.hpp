#pragma once
#include <filesystem>
                                    
namespace fs = std::filesystem;

std::optional<fs::path> CreateNewEntry(fs::path nook_dir);
