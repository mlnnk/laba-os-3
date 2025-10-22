# CMakeList.txt: проект CMake для cpp2017; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cpp2017")


add_library(mylib
    src/marker_logic.cpp
    src/marker_thread.cpp
)
target_include_directories(mylib PUBLIC ${CMAKE_SOURCE_DIR}/src)


add_executable (Laba3-cpp2017 "cpp2017.cpp")
target_include_directories(Laba3-cpp2017 PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Laba3-cpp2017 PRIVATE mylib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include(FetchContent)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#FetchContent_Declare(
 # googletest
 # URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
#)

#set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

#FetchContent_MakeAvailable(googletest)



#add_executable(Unit_tests Unit_tests/Unit_tests.cpp)
#target_link_libraries(Unit_tests PRIVATE mylib GTest::gtest_main)

#include(GoogleTest)
#gtest_discover_tests(Unit_tests)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.

