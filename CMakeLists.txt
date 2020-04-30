cmake_minimum_required(VERSION 3.12)
project(JsonParser)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(DFG_LEXER ${CMAKE_CURRENT_SOURCE_DIR}/src/json.l
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.lex.cc
  DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/json.lex.h)

BISON_TARGET(DFG_PARSER ${CMAKE_CURRENT_SOURCE_DIR}/src/json.y
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.tab.cc
  DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/json.tab.h)

add_library(json
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.lex.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.tab.cc)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)

include_directories(main ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(main json)
target_compile_options(main PRIVATE "-g")
