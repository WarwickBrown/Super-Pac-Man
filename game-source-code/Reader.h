/**
 * @file Reader.h
 * @brief Defines the Reader class, which provides functionality for file operations.
 * 
 * The Reader class handles reading from, writing to, and deleting files. It stores the
 * contents of a file as a vector of strings and provides getter and setter methods to
 * access and modify the data. This class can be used to handle various file operations
 * required for different game components, such as configuration or maze data.
 */

#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/**
 * @class Reader
 * @brief A class that provides file reading, writing, and deletion functionalities.
 * 
 * The Reader class encapsulates basic file operations, including reading data from a file,
 * writing data to a file, and deleting a specified file. It stores file data as a vector
 * of strings, allowing easy manipulation of file content.
 */
class Reader {
protected:
    std::vector<std::string> data;  ///< Vector to store lines of text read from the file.
    std::string fileName;           ///< Name of the file to be read, written, or deleted.

public:
    /**
     * @brief Constructs a Reader object with a specified file path.
     * 
     * This constructor initialises the Reader with a given file path or uses a default path
     * if none is specified.
     * 
     * @param filePath The path of the file to be read or written (default is "../resources/walls.txt").
     */
    Reader(const std::string& filePath = "../resources/database-textfiles/walls.txt");
/**
     * @brief Reads data from the file specified by `fileName`.
     * 
     * This method opens the file in read mode and stores each line in the `data` vector.
     * If the file cannot be opened, an error message is displayed.
     */
    void readFile();

    /**
     * @brief Writes data to the file specified by `fileName`.
     * 
     * This method opens the file in write mode and writes each line from the provided vector `lines`
     * to the file. If the file cannot be opened, an error message is displayed.
     * 
     * @param lines A vector of strings containing the data to be written to the file.
     */
    void writeFile(const std::vector<std::string>& lines);

    /**
     * @brief Gets the data read from the file.
     * 
     * This method returns a constant reference to the vector containing the data read from the file.
     * 
     * @return A constant reference to the `data` vector containing the file content.
     */
    const std::vector<std::string>& getData() const;

    /**
     * @brief Sets the internal data vector with new data.
     * 
     * This method replaces the existing data stored in the `data` vector with the provided `newData`.
     * 
     * @param newData A vector of strings containing the new data to be stored.
     */
    void setData(const std::vector<std::string>& newData);

    /**
     * @brief Deletes the specified file from the file system.
     * 
     * This method deletes the file specified by `tempFileName`. If the file is successfully deleted,
     * a success message is displayed. If the deletion fails, an error message is shown.
     * 
     * @param tempFileName The name of the file to be deleted.
     */
    void deleteFile(std::string tempFileName);
};

#endif // READER_H