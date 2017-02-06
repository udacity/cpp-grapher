cmake_minimum_required(VERSION 3.5)

project(cpp-grapher)

set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_STANDARD 14)

set(CLANG_CXX_WALL "-Weverything -Werror -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-exit-time-destructors -Wno-weak-vtables")
#set(CLANG_CXX_FLAGS "-std=${CXX_STANDARD} ${CLANG_CXX_WALL} -I/usr/local/include/ImageMagick-7/")
set(CLANG_CXX_FLAGS "-std=${CXX_STANDARD} -I/usr/local/include/ImageMagick-7/")

set(GCC_CXX_WALL "-Wall -Wpedantic -Werror")
#set(GCC_CXX_FLAGS "-std=${CXX_STANDARD} ${GCC_CXX_WALL} -I/usr/local/include/ImageMagick-7/")
set(GCC_CXX_FLAGS "-std=${CXX_STANDARD} -I/usr/local/include/ImageMagick-7/")

set(MSVC_CXX_WALL "/W4")
set(MSVC_CXX_FLAGS "/std:${CXX_STANDARD} ${MSVC_CXX_WALL}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS}")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CXX_FLAGS}")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_CXX_FLAGS}")
endif()

add_subdirectory(Sources)
