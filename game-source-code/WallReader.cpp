#include "WallReader.h"

// Method to read data from a text file
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
