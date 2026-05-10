#pragma once

#include <filesystem>

namespace fs = std::filesystem;

void EnsureVimrcExists(const fs::path& config_dir);

