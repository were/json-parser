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

enable_testing()
file(GLOB_RECURSE TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

foreach(test ${TESTS})
  get_filename_component(test_name ${test} NAME_WE)
  add_executable(${test_name} ${test})
  target_link_libraries(${test_name} minijson)
  include_directories(${test_name} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
  add_test(NAME ${test_name}
           COMMAND $<TARGET_FILE:${test_name}> ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_jsons/basic.json) 
endforeach()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)
install(TARGETS minijson DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)
