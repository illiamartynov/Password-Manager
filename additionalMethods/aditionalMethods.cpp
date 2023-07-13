
#include <fstream>
#include "aditionalMethods.h"

void aditionalMethods::deleteFirstLine(const std::string &filename) {
    std::fstream file(filename, std::ios::in | std::ios::out);

    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::string firstLine;
        std::getline(file, firstLine);

        if (!firstLine.empty()) {
            fileSize -= firstLine.size() + 1;
            file.seekg(firstLine.size() + 1, std::ios::beg);
            char* buffer = new char[fileSize];
            file.read(buffer, fileSize);
            file.seekp(0, std::ios::beg);
            file.write(buffer, fileSize);
            delete[] buffer;
        }

        file.seekp(fileSize, std::ios::beg);
        file.close();
    }
}

void aditionalMethods::writeNewTimeToFirstLine(const std::string &filename, const std::string &newTime) {
    std::fstream file(filename, std::ios::in | std::ios::out);

    if (file.is_open()) {
        file.seekp(0, std::ios::beg);
        file << newTime << std::endl;
        file.close();
    }
}
