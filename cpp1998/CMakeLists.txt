
cmake_minimum_required(VERSION 3.8)

project(cpp1998 LANGUAGES CXX)


add_library(cpp1998lib
    src/marker_logic.cpp
    src/marker_thread.cpp
)

target_include_directories(cpp1998lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(Laba3-cpp1998 cpp1998.cpp)
target_include_directories(Laba3-cpp1998 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Laba3-cpp1998 PRIVATE cpp1998lib)

#
set_target_properties(cpp1998lib PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES)
set_target_properties(Laba3-cpp1998 PROPERTIES CXX_STANDARD 98 CXX_STANDARD_REQUIRED YES)
