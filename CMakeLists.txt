cmake_minimum_required(VERSION 3.24)
project(quest3)

set(CMAKE_CXX_STANDARD 17)

add_executable(quest3 main.cpp)

target_link_directories(quest3 PRIVATE lib)
target_link_libraries(quest3 PRIVATE libOVR)
target_include_directories(quest3 PRIVATE inc)