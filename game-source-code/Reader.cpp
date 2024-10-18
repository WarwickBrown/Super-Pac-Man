/**
 * @file Reader.cpp
 * @brief Implements the Reader class, which handles file reading, writing, and deletion operations.
 * 
 * The Reader class provides methods to read data from a file, write data to a file, and delete a file.
 * It also includes getter and setter functions for the data stored in memory.
 */

#include "Reader.h"
#include <iostream>
#include <fstream>

Reader::Reader(const std::string& filePath) : fileName(filePath) {}

void Reader::readFile() {
    std::ifstream file(fileName);  ///< Input file stream to read data from the file.
    if (!file) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);  ///< Store each line of the file in the vector.
    }

    file.close();  ///< Close the file after reading.
}

void Reader::writeFile(const std::vector<std::string>& lines) {
    std::ofstream file(fileName);  ///< Output file stream to write data to the file.
    if (!file) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    for (const auto& line : lines) {
        file << line << "\n";  ///< Write each line to the file.
    }

    file.close();  ///< Close the file after writing.
}

const std::vector<std::string>& Reader::getData() const {
    return data;
}

void Reader::setData(const std::vector<std::string>& newData) {
    data = newData;
}

void Reader::deleteFile(std::string tempFileName) {
    if (std::remove(tempFileName.c_str()) == 0) {
        std::cout << "File " << tempFileName << " deleted successfully." << std::endl;
    } else {
        std::cerr << "Error: Could not delete file " << tempFileName << std::endl;
    }
}