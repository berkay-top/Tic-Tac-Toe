cmake_minimum_required(VERSION 3.11)
project(Tic-Tac-Toe)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FTXUI -----------------------------------------
include(FetchContent)

FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# executables ------------------------------------
add_executable(ttt src/main.cpp src/bestMove.cpp src/gridCheck.cpp)
target_link_libraries(ttt PRIVATE ftxui::component)
