cmake_minimum_required(VERSION 3.10)

project(SuperSocket C CXX)

#set toolchain
SET(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

#设置使用c++14标准
set(CMAKE_CXX_STANDARD 14)

#project directory
include_directories(${PROJECT_SOURCE_DIR}../include)#czmq header
#link_directories
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}../lib)#czmq lib

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

aux_source_directory(. SRC_LIST)
#file(GLOB LIB_LIST "/home/forlinx/Workspace/A_myself/Radar/lib/lib*.a*")
file(GLOB LIB_LIST ${PROJECT_SOURCE_DIR} "../lib/lib*.a*")
#add_library(SuperSocket SHARED ${SRC_LIST})//动态库
add_library(SuperSocket ${SRC_LIST})
target_link_libraries(SuperSocket ${LIB_LIST} pthread)
