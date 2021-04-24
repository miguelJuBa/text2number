cmake_minimum_required(VERSION 3.10)
project(text2number)

set(CMAKE_CXX_STANDARD 14)

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS log REQUIRED)

add_subdirectory(src)
add_subdirectory(test)