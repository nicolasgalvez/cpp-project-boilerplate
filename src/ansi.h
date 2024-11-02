// https://manytools.org/hacker-tools/convert-image-to-ansi-art/go/
#ifndef ANSI_H
#define ANSI_H

#include <iostream>
#include <fstream>
#include <string>

// Function to read the .ans file into a string
std::string readAnsiFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// Function to display the ANSI art to the terminal
void displayAnsiArt(const std::string& ansiArt) {
    std::cout << ansiArt << std::endl;
}

#endif // ANSI_H