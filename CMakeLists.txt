cmake_minimum_required(VERSION 4.0)
project(cppLabGame)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)


add_executable(cppLabGame main.cpp)


target_link_libraries(cppLabGame ${NCURSES_LIBRARIES})
target_include_directories(cppLabGame PRIVATE ${NCURSES_INCLUDE_DIRS})