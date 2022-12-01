cmake_minimum_required(VERSION 3.10)

project(SuperSocketTest C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")#Release
endif()

#set ouput path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# 查找当前目录下的所有源文件 并将名称保存到 SRC_LIST 变量
aux_source_directory(. SRC_LIST)

#file(GLOB LIB_LIST "/home/forlinx/Workspace/A_myself/Radar/lib/lib*.a*")
file(GLOB LIB_LIST ${PROJECT_SOURCE_DIR} "../lib/lib*.a*")
add_executable(SuperSocketTest ${SRC_LIST})
target_link_libraries(SuperSocketTest ${LIB_LIST} pthread dl) 
