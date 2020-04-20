#include <iostream>
#include "FileStream.h"
#include "STB.h"

int errorCount = 0;

int desiredChannels = 0;

bool isFlip = false;

bool convertImage(const char* path){
    std::cout << "Processing " << path << "..." << std::endl;
    int width, height, nrComponents;
    auto toProcess = new std::string;
    toProcess->append("Input/");
    toProcess->append(path);
    stbi_set_flip_vertically_on_load(isFlip);
    uint8_t* data = stbi_load(toProcess->c_str(), &width, &height, &nrComponents, desiredChannels);
    if(desiredChannels == 0)
        desiredChannels = nrComponents;
    if (data == nullptr) {
        std::cout << "Failed to load Image: " << path << std::endl;
        errorCount += 1;
        return false;
    }else {
        LibString filename("Output/");
        filename += getFilename((char*)path);
        filename = filename.substring(0, filename.findLast("."));
        filename += ".bif";
        Binary_buffer binaryBuffer;
        binary_buffer_create(&binaryBuffer, 5000000);
        auto widthData = (uint64_t)width;
        binary_buffer_push64(&binaryBuffer, widthData);
        auto heightData = (uint64_t)height;
        binary_buffer_push64(&binaryBuffer, heightData);
        auto compData = (uint64_t)desiredChannels;
        binary_buffer_push64(&binaryBuffer, compData);
        binary_buffer_push_string_with_termination(&binaryBuffer, (char*)data, width * height * desiredChannels);
        binary_buffer_write_to_file(&binaryBuffer, filename.toString());
        free(data);
        binary_buffer_destroy(&binaryBuffer);
    }
    toProcess->clear();
    delete toProcess;
    return true;
}

int main(int argc, char *argv[]){
    std::vector<std::string> files;
    if(isFlip)
        files = getFilenames(argv[0], 22);
    else
        files = getFilenames(argv[0], 18);
    if(files.empty()) {
        std::cout << "Failed to locate Files" << std::endl;
        system("pause");
        return 0;
    }
    std::cout << "Desired Channels: ";
    std::cin >> desiredChannels;
    for(auto file : files){
        convertImage(file.data());
    }
    std::cout << "Finished with " << errorCount << " Errors." << std::endl;
    system("pause");
    return 0;
}