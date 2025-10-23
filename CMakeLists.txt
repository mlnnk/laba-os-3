cmake_minimum_required(VERSION 3.16)
project(MyMarkers LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(cpp2017)
add_subdirectory(cpp1998)


include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(Unit_tests_2017 Unit_tests/Unit_tests.cpp)
target_link_libraries(Unit_tests_2017 PRIVATE cpp2017lib GTest::gtest_main)
set_target_properties(Unit_tests_2017 PROPERTIES CXX_STANDARD 17)


add_executable(Unit_tests_1998 Unit_tests/Unit_tests.cpp)
target_link_libraries(Unit_tests_1998 PRIVATE cpp1998lib GTest::gtest_main)
set_target_properties(Unit_tests_1998 PROPERTIES CXX_STANDARD 98)

include(GoogleTest)
gtest_discover_tests(Unit_tests_2017)
gtest_discover_tests(Unit_tests_1998)
