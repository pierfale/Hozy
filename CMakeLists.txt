cmake_minimum_required(VERSION 2.6)

project(Hozy)

#define
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Werror -Wall -std=gnu++0x")

include_directories(include)

#include file
file(
        GLOB_RECURSE
        include_files
        include/*
)

#src file
file(
        GLOB_RECURSE
        source_files
        src/*
)


add_executable(
        Game

        ${include_files}
	${source_files}
)

