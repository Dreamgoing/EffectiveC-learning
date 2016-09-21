cmake_minimum_required(VERSION 3.6)
project(EffectiveC__learning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES chapter00.cpp)
add_executable(chapter00 ${SOURCE_FILES})