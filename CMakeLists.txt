cmake_minimum_required(VERSION 3.15)
project(ImageConverter)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")

add_executable(ImageConverter ImageConverter/Main.cpp ImageConverter/LibString.cpp ImageConverter/LibString.h ImageConverter/FileStream.h ImageConverter/FileStream.cpp ImageConverter/STB.cpp ImageConverter/STB.h)