#include "WallReader.h"

// Constructor to accept a custom file path
WallReader::WallReader(const std::string& filePath) : fileName(filePath) {}

// Read data from the file
void WallReader::readFile() {
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
void WallReader::writeFile(const std::vector<std::string>& lines) {
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
const std::vector<std::string>& WallReader::getData() const {
    return data;
}

// Setter for the data 
void WallReader::setData(const std::vector<std::string>& newData) {
    data = newData;
}
