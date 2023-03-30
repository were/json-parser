cmake_minimum_required(VERSION 3.12)
project(JsonParser)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

include(CTest)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(DFG_LEXER ${CMAKE_CURRENT_SOURCE_DIR}/src/json.l
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.lex.cc
  DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/json.lex.h)

BISON_TARGET(DFG_PARSER ${CMAKE_CURRENT_SOURCE_DIR}/src/json.y
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.tab.cc
  DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/json.tab.h)

add_library(minijson
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.lex.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/json.tab.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/printer.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/value.cc)

add_executable(fixed-point ${CMAKE_CURRENT_SOURCE_DIR}/test/fixed-point.cpp)

# testing binary
add_executable(basic_tests ${CMAKE_CURRENT_SOURCE_DIR}/test/basic.cpp)
target_link_libraries(basic_tests minijson)

# enable testing functionality
enable_testing()

add_test(NAME basic_tests
         COMMAND $<TARGET_FILE:basic_tests> ${CMAKE_CURRENT_SOURCE_DIR}/test/test_jsons/basic.json)


include_directories(fixed-point ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(fixed-point minijson)
target_compile_options(fixed-point PRIVATE "-g")

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)
install(TARGETS minijson DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)
