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

struct _Binary_buffer {
    uint8_t* _byte_array;
    uint64_t _bytes;
    uint64_t _bytes_off;
};

typedef _Binary_buffer Binary_buffer;
typedef _Binary_buffer& Binary_buffer_reference;
typedef _Binary_buffer const Binary_buffer_const;
typedef _Binary_buffer* Binary_buffer_pointer;
typedef _Binary_buffer* const Binary_buffer_const_pointer;

void binary_buffer_create(Binary_buffer_pointer buffer, uint64_t alloc_size);
void binary_buffer_destroy(Binary_buffer_pointer buffer);
uint8_t binary_buffer_pop8(Binary_buffer_pointer buffer);
uint16_t binary_buffer_pop16(Binary_buffer_pointer buffer);
uint32_t binary_buffer_pop32(Binary_buffer_pointer buffer);
uint64_t binary_buffer_pop64(Binary_buffer_pointer buffer);
float binary_buffer_pop_float(Binary_buffer_pointer buffer);
const char* binary_buffer_pop_string(Binary_buffer_pointer buffer, uint64_t string_size);
const char* binary_buffer_pop_string_with_termination(Binary_buffer_pointer buffer, uint64_t string_size);
void binary_buffer_push8(Binary_buffer_pointer buffer, uint8_t u8);
void binary_buffer_push16(Binary_buffer_pointer buffer, uint16_t u16);
void binary_buffer_push32(Binary_buffer_pointer buffer, uint32_t u32);
void binary_buffer_push64(Binary_buffer_pointer buffer, uint64_t u64);
void binary_buffer_push_float(Binary_buffer_pointer buffer, float f32);
void binary_buffer_push_string(Binary_buffer_pointer buffer, const char* string);
void binary_buffer_push_string_with_termination(Binary_buffer_pointer buffer, const char* string, uint64_t size);

typedef const char* Path;

void binary_buffer_read_from_file(Binary_buffer_pointer buffer, Path file_path);
void binary_buffer_write_to_file(Binary_buffer_pointer buffer, Path file_path);

static std::vector<const char*> endings = { "png","bmp","jpeg","jpg","hdr","psd","tga","gif","pic","ppm" };
char* getFilename(char* filename);
const char* toLow(const char* string);
bool contains(const char* searchFor, const char* searchIn);
std::vector<std::string> getFilenames(char* exePath, int something);