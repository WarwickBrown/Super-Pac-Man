#ifndef WALLREADER_H
#define WALLREADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class WallReader {
    protected:
        std::vector<std::string> data;  // Vector to store lines of text from the file

    public:
        // Declaration of readFile (no definition here)
        void readFile();

        // Getter for the data 
        const std::vector<std::string>& getData() const {
            return data;
        }
        
    private:
        const std::string fileName = "../resources/walls.txt";
};

#endif // WALLREADER_H
