cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(linked_data_map_test VERSION 1.0)
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(benchmark)
add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main benchmark::benchmark)
target_sources(${PROJECT_NAME} PRIVATE "src/linked_data_map_test.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)