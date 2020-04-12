#pragma once

#include <cstdint>
#include <cstdio>
#include <malloc.h>
#include "LibString.h"
#include <vector>
#include <cstring>
#include <windows.h>
#include <cctype>
#include <tchar.h>

static std::vector<const char*> endings = { "png","bmp","jpeg","jpg","hdr","psd","tga","gif","pic","ppm" };

bool openFile(const LibString path, const LibString mode);
void closeFile();
bool writeToFile(void* data, uint64_t elements, uint64_t elementSize);
void* readFromFile(uint64_t elements, uint64_t elementSize);
template<typename T>
bool writeToFile(void* data, uint64_t elements) {
    return writeToFile(data, elements, sizeof(T));
}
template<typename T>
T readFromFile(uint64_t elements) {
    void* data  = readFromFile(elements, sizeof(T));
    T t;
    if(data == nullptr) return t;
    t = *(T*)data;
    free(data);
    return t;
}

bool writeStringToFile(uint8_t* data, uint64_t size);
uint8_t* readStringFromFile();

char* getFilename(char* filename);
const char* toLow(const char* string);
bool contains(const char* searchFor, const char* searchIn);
std::vector<std::string> getFilenames(char* exePath, int exeLength);