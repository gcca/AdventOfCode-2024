cmake_minimum_required(VERSION 3.30)
project(
  AdventOfCode2024
  VERSION 0.0.1
  LANGUAGES CXX)

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(
  AdventOfCode2024
  day01.cc
  day02.cc
  day03.cc
  day04.cc
  day05.cc
  day06.cc
  day07.cc
  day08.cc
  day09.cc
  day10.cc
  day11.cc
  day12.cc
  day13.cc
  day14.cc
  day15.cc)
target_link_libraries(AdventOfCode2024 GTest::GTest GTest::Main)
target_compile_options(
  AdventOfCode2024
  PUBLIC -Wall
         -Wextra
         -Werror
         -Wpedantic
         -Wshadow
         -Weverything
         -Wconversion
         -Wsign-conversion
         -Wnon-virtual-dtor
         -Wold-style-cast
         -Wfloat-equal
         -Wformat=2
         -Wnull-dereference
         -Wundef
         -Wuninitialized
         -Wcast-align
         -Wformat-security
         -Wstrict-overflow
         -Wswitch-enum
         -Wunused-variable
         -Wunused-parameter
         -Wpointer-arith
         -Wcast-align
         -Wno-variadic-macros
         -fexceptions
         -fsafe-buffer-usage-suggestions
         -Wno-c++98-compat
         -Wno-padded
         -Wno-covered-switch-default
         -Wno-unsafe-buffer-usage
         -Wno-c++98-compat-pedantic
         -Wno-global-constructors
         -Wno-weak-vtables)

gtest_discover_tests(AdventOfCode2024)
