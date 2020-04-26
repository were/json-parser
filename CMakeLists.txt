cmake_minimum_required(VERSION 3.12)
project(JsonParser)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(DFG_LEXER ${CMAKE_SOURCE_DIR}/src/json.l
  ${CMAKE_SOURCE_DIR}/src/json.lex.cc
  DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/json.lex.h)

BISON_TARGET(DFG_PARSER ${CMAKE_SOURCE_DIR}/src/json.y
  ${CMAKE_SOURCE_DIR}/src/json.tab.cc
  DEFINES_FILE ${CMAKE_SOURCE_DIR}/src/json.tab.h)

add_executable(main
  ${CMAKE_SOURCE_DIR}/src/json.lex.cc
  ${CMAKE_SOURCE_DIR}/src/json.tab.cc)

include_directories(main ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
