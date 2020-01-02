
cmake_minimum_required(VERSION 3.10)

# set the project name
project(Hello)

set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TEST_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(TEST_THIRDPARTY_DIR ${TEST_BINARY_DIR}/third_party)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add the executable 
add_executable(Hello hello.c)

if(NOT TARGET cpuinfo)
  #Download cpuinfo from github if CPUINFO_SOURCE_DIR is not specified.
  if(NOT DEFINED CPUINFO_SOURCE_DIR)
    set(CPUINFO_SOURCE_DIR "${TEST_SOURCE_DIR}/third_party/cpuinfo"
      CACHE STRING "cpuinfo source directory from submodules")
  endif()

  #build cpuinfo
  set(CPUINFO_BUILD_UNIT_TESTS OFF CACHE BOOL "Do not build cpuinfo unit tests")
  set(CPUINFO_BUILD_MOCK_TESTS OFF CACHE BOOL "Do not build cpuinfo mock tests")
  set(CPUINFO_BUILD_BENCHMARKS OFF CACHE BOOL "Do not build cpuinfo benchmarks")
  set(CPUINFO_LIBRARY_TYPE static)
  add_subdirectory("${CPUINFO_SOURCE_DIR}" "${TEST_BINARY_DIR}/cpuinfo")
  set_property(TARGET cpuinfo PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_include_directories(Hello BEFORE
      PUBLIC $<BUILD_INTERFACE:${TEST_SOURCE_DIR}>
      PUBLIC $<BUILD_INTERFACE:${TEST_SOURCE_DIR}/include>
      PRIVATE "${CPUINFO_SOURCE_DIR}/include")

target_link_libraries(Hello cpuinfo)
add_dependencies(Hello cpuinfo)


