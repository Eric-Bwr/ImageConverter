#include <iostream>
#include "FileStream.h"
#include "STB.h"

int errorCount = 0;

bool isFlip = true;

bool convertImage(const char* path){
    std::cout << "Processing " << path << "..." << std::endl;
    int width, height, nrComponents;
    auto toProcess = new std::string;
    toProcess->append("Input/");
    toProcess->append(path);
    stbi_set_flip_vertically_on_load(isFlip);
    uint8_t* data = stbi_load(toProcess->c_str(), &width, &height, &nrComponents, 0);
    if (data == nullptr) {
        std::cout << "Failed to load Image: " << path << std::endl;
        errorCount += 1;
        return false;
    }else {
        std::string filename("Output/");
        filename.append(std::string(getFilename((char *) path)));
        std::string filenameWithoutExtension = filename.substr(0, filename.find_last_of('.'));
        std::string outputFilename = filenameWithoutExtension + ".bif";
        openFile(outputFilename.c_str(), "wb");
        writeToFile<int>(&width, 1);
        writeToFile<int>(&height, 1);
        writeToFile<int>(&nrComponents, 1);
        writeToFile<uint8_t>(data, width * height * nrComponents);
        closeFile();
        free(data);
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
        std::cout << "Failed to load Files" << std::endl;
        system("pause");
        return 0;
    }
    for(auto file : files){
        convertImage(file.data());
    }
    std::cout << "Finished with " << errorCount << " Errors." << std::endl;
    system("pause");
    return 0;
}