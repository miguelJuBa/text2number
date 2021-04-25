cmake_minimum_required(VERSION 3.10)
project(text2number)

add_compile_options(-Wall -Werror -Wno-error=maybe-uninitialized)
set(CMAKE_CXX_STANDARD 14)

set(RELEASE_FLAGS "-Ofast -DNDEBUG -DBOOST_DISABLE_ASSERTS")
set(DEBUG_FLAGS "-O0 -ggdb3")

set(CMAKE_CXX_FLAGS_RELEASE ${RELEASE_FLAGS})
set(CMAKE_C_FLAGS_RELEASE ${RELEASE_FLAGS})

set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})
set(CMAKE_C_FLAGS_DEBUG ${DEBUG_FLAGS})

ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS log REQUIRED)

add_subdirectory(src)
add_subdirectory(test)