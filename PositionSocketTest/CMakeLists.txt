cmake_minimum_required(VERSION 3.10)

project(PositionSocketTest C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")#Release
endif()

#设置使用c++14标准
set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

#project directory
#include_directories(${PROJECT_SOURCE_DIR}../include) #vcpkg

#link_directories
#LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}../lib) #vcpkg

#set ouput path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 查找当前目录下的所有源文件 并将名称保存到 SRC_LIST 变量
aux_source_directory(. SRC_LIST)

#file(GLOB LIB_LIST "/home/forlinx/Workspace/A_myself/Radar/lib/lib*.a*")
file(GLOB LIB_LIST ${PROJECT_SOURCE_DIR} "../lib/lib*.a*")
add_executable(PositionSocketTest ${SRC_LIST})
target_link_libraries(PositionSocketTest ${LIB_LIST} pthread dl) 
