#ifndef WALLREADER_H
#define WALLREADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class WallReader {
protected:
    std::vector<std::string> data;  // Vector to store lines of text from the file
    std::string fileName;           // The file name is now flexible.

public:
    // Constructor to accept a custom file path
    WallReader(const std::string& filePath = "../resources/walls.txt");

    // Read data from the file
    void readFile();

    // Write data to the file
    void writeFile(const std::vector<std::string>& lines);

    // Getter for the data 
    const std::vector<std::string>& getData() const;

    // Setter for the data 
    void setData(const std::vector<std::string>& newData);
};

#endif // WALLREADER_H
