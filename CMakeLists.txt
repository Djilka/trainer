cmake_minimum_required(VERSION 2.8.9)
project(train)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(train main.cpp)
target_link_libraries(train stdc++fs)
