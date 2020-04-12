cmake_minimum_required(VERSION 3.15)
project(ImageConverter)

set(CMAKE_CXX_STANDARD 17)

add_executable(ImageConverter ImageConverter/Main.cpp ImageConverter/LibString.cpp ImageConverter/LibString.h ImageConverter/FileStream.h ImageConverter/FileStream.cpp ImageConverter/STB.cpp ImageConverter/STB.h)