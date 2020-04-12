#include "FileStream.h"

FILE* file = nullptr;

bool openFile(const LibString path, const LibString mode) {
    file = fopen(path.toString(), mode.toString());
    return file != nullptr;
}

void closeFile() {
    if(file != nullptr) {
        fclose(file);
        file = nullptr;
    }
}

bool writeToFile(void* data, uint64_t elements, uint64_t elementSize) {
    if(file == nullptr) return false;

    int result = fwrite(data, elementSize, elements, file);
    return result == elements;
}

void* readFromFile(uint64_t elements, uint64_t elementSize) {
    if(file == nullptr) return nullptr;

    uint64_t allocSize = elements * elementSize;
    void *data = malloc(allocSize);
    int result = fread(data, elementSize, elements, file);
    if(result != elements) return nullptr;
    return data;
}

bool writeStringToFile(uint8_t* data, uint64_t size) {
    if(!writeToFile(&size, 1, sizeof(uint64_t))) return false;
    return writeToFile(&data, 1, sizeof(char) * size);
}

uint8_t* readStringFromFile() {
    auto sizeData = readFromFile<uint64_t>(1);
    void* string = readFromFile(1, sizeof(uint8_t) * sizeData);
    return (uint8_t*)string;
}

bool contains(const char* searchFor, const char* searchIn) {
    uint64_t forlen = strlen(searchFor);
    uint64_t inLen = strlen(searchIn);
    for(uint64_t i =  0; i < inLen; i ++) {
        if(searchIn[i] == searchFor[0]) {
            for(uint64_t j = 0; j < forlen; j++) {
                if(searchIn[i + j] != searchFor[j]) {
                    break;
                } else {
                    if(j == forlen - 1) return true;
                }
            }
        }
    }
    return false;
}

char* getFilename(char* filename) {
    int len = strlen(filename);
    char* lastSlash = filename;
    for (int i = 0; i < len; i++) {
        if (filename[i] == '/' || filename[i] == '\\') {
            lastSlash = filename + i + 1;
        }
    }
    return lastSlash;
}

const char* toLow(const char* string ) {
    uint64_t len = strlen(string);
    char* stringLow = (char*)malloc(len * sizeof(char));
    for(uint64_t i = 0; i < len; i++)
        stringLow[i] = (char)tolower((int)string[i]);
    stringLow[len] = '\0';
    return stringLow;
}

std::vector<std::string> getFilenames(char* exePath, int exeLength) {
    auto folderPath = new std::string(exePath);
    folderPath->erase(folderPath->end() - exeLength, folderPath->end());
    folderPath->append("\\Input");
    WIN32_FIND_DATA wfd;
    HANDLE handle;
    folderPath->append("/*");
    TCHAR* path = (TCHAR*)(folderPath->data());
    std::vector<std::string> filenames;
    handle = FindFirstFile(path, &wfd);
    while (FindNextFile(handle, &wfd)) {
        if (!strcmp((char*)wfd.cFileName, "..") == 0){
            for(auto toCompare : endings){
                if(contains(toCompare, toLow(wfd.cFileName))){
                    filenames.emplace_back(wfd.cFileName);
                    break;
                }
            }
        }
    }
    FindClose(handle);
    folderPath->clear();
    delete folderPath;
    return filenames;
}