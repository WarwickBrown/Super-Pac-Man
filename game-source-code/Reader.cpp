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

/**
 * @brief Constructs a Reader object with a specified file path.
 * 
 * This constructor initialises the Reader object and sets the file path to be used
 * for reading and writing operations.
 * 
 * @param filePath The path of the file to be read or written.
 */
Reader::Reader(const std::string& filePath) : fileName(filePath) {}

/**
 * @brief Reads data from the file and stores it in the internal data vector.
 * 
 * This method opens the file specified by `fileName` and reads its content line by line,
 * storing each line in the `data` vector. If the file cannot be opened, an error message
 * is displayed.
 */
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

/**
 * @brief Writes data to the file specified by `fileName`.
 * 
 * This method opens the file specified by `fileName` in output mode and writes each line
 * from the provided vector `lines` to the file. If the file cannot be opened, an error
 * message is displayed.
 * 
 * @param lines A vector of strings containing the data to be written to the file.
 */
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

/**
 * @brief Gets the data read from the file.
 * 
 * This method returns a constant reference to the vector containing the data read from the file.
 * 
 * @return A constant reference to the `data` vector.
 */
const std::vector<std::string>& Reader::getData() const {
    return data;
}

/**
 * @brief Sets the internal data vector with new data.
 * 
 * This method replaces the existing data stored in the `data` vector with the provided `newData`.
 * 
 * @param newData A vector of strings containing the new data to be stored.
 */
void Reader::setData(const std::vector<std::string>& newData) {
    data = newData;
}

/**
 * @brief Deletes the specified file.
 * 
 * This method deletes the file specified by `tempFileName`. If the file is successfully deleted,
 * a success message is displayed. If not, an error message is shown.
 * 
 * @param tempFileName The name of the file to be deleted.
 */
void Reader::deleteFile(std::string tempFileName) {
    if (std::remove(tempFileName.c_str()) == 0) {
        std::cout << "File " << tempFileName << " deleted successfully." << std::endl;
    } else {
        std::cerr << "Error: Could not delete file " << tempFileName << std::endl;
    }
}
