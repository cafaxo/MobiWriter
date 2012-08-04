//
//  MobiBook.cpp
//  MobiWriter
//

#include "MobiBook.h"

MobiBook::MobiBook(std::string title, std::string author) {
    title_ = title;
    author_ = author;
}

bool MobiBook::addHtmlFile(std::string filename) {
    std::ifstream file(filename.c_str(), std::ifstream::in);

    if (!file.is_open()) {
        std::cout << "couldn't open html file: " << filename << std::endl;
        return false;
    }
    
    file.seekg(0, std::ios::end);
    size_t length = file.tellg();
    file.seekg(0, std::ios::beg);
    
    char *buffer = new char [length];
    
    file.read(buffer, length);
    file.close();
    
    html_content_.append(std::string(buffer));
    delete[] buffer;
    
    return true;
}
