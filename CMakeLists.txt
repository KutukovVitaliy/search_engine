cmake_minimum_required(VERSION 3.20)
project(search_engine)
set(CMAKE_CXX_STANDARD 17)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL
#        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#set(gtest_disable_pthreads on)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#enable_testing()
#include(GoogleTest)


add_subdirectory(nlohmann_json)
add_executable(search_engine main.cpp ConverterJSON.cpp ConverterJSON.h InvertedIndex.cpp InvertedIndex.h)
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(search_engine PRIVATE gtest_main)
#gtest_discover_tests(search_engine)