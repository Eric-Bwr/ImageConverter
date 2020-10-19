cmake_minimum_required(VERSION 3.15)
project(ImageConverter)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(ImageConverter ImageConverter/Main.cpp ImageConverter/LibString.cpp ImageConverter/LibString.h ImageConverter/FileStream.h ImageConverter/FileStream.cpp ImageConverter/STB.cpp ImageConverter/STB.h)