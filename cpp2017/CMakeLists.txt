
cmake_minimum_required(VERSION 3.8)

project(cpp2017 LANGUAGES CXX)


add_library(cpp2017lib
    src/marker_logic.cpp
    src/marker_thread.cpp
)

target_include_directories(cpp2017lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(Laba3-cpp2017 cpp2017.cpp)
target_include_directories(Laba3-cpp2017 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Laba3-cpp2017 PRIVATE cpp2017lib)

#
set_target_properties(cpp2017lib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
set_target_properties(Laba3-cpp2017 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
