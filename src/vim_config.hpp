#pragma once
#include <filesystem>

namespace fs = std::filesystem;

void EnsureConfigExists(const fs::path& nook_dir);

