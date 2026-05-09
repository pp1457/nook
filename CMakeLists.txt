cmake_minimum_required(VERSION 3.20)
project(nook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json for your editor's LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG        v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_executable(nook 
  src/main.cpp
  src/home_screen.cpp
  src/entry.cpp
  src/vim_config.cpp
)#

target_include_directories(nook PRIVATE src)

target_link_libraries(nook
  PRIVATE
    ftxui::component
    ftxui::dom
    ftxui::screen
)

# Reasonable warnings — catch mistakes early
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(nook PRIVATE -Wall -Wextra -Wpedantic)
endif()
