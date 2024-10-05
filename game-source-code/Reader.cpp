#include "Reader.h"

// Constructor to accept a custom file path
Reader::Reader(const std::string& filePath) : fileName(filePath) {}

// Read data from the file
void Reader::readFile() {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);  // Store each line of the file in the vector
    }

    file.close();
}

// Write data to the file
void Reader::writeFile(const std::vector<std::string>& lines) {
    std::ofstream file(fileName);
    if (!file) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    for (const auto& line : lines) {
        file << line << "\n";
    }

    file.close();
}

// Getter for the data 
const std::vector<std::string>& Reader::getData() const {
    return data;
}

// Setter for the data 
void Reader::setData(const std::vector<std::string>& newData) {
    data = newData;
}
