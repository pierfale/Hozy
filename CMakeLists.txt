cmake_minimum_required(VERSION 2.6)

project(Hozy)

#define
#set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++0x -Wall -Werror -Wextra -Wshadow -Weffc++ -Wstrict-aliasing -pedantic")

include_directories(include)
aux_source_directory(. SRC_LIST)

#operating system
if(UNIX)
	set(OS "UNIX")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
if(WIN32)
	set(OS "WIN32")
	
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${OS}")

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



#client
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/${CMAKE_BUILD_TYPE}/client)
set(client_sources_files ${source_files})
list(REMOVE_ITEM client_sources_files ${CMAKE_CURRENT_SOURCE_DIR}/src/server/MainServer.cpp)

add_executable(
	Hozy_Client

	${include_files}
	${client_sources_files}
)

#client lib
if(WIN32)
	target_link_libraries(Hozy_Client "ws2_32.lib")
	target_link_libraries(Hozy_Client "DbgHelp.lib")
endif()

#server
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/${CMAKE_BUILD_TYPE}/server)
set(server_sources_files ${source_files})
list(REMOVE_ITEM server_sources_files ${CMAKE_CURRENT_SOURCE_DIR}/src/client/MainClient.cpp)

add_executable(
	Hozy_Server

	${include_files}
	${server_sources_files}
)

#server lib
if(WIN32)
target_link_libraries(Hozy_Server "ws2_32.lib")
target_link_libraries(Hozy_Server "DbgHelp.lib")
endif()
