//
//  MobiBook.cpp
//  MobiWriter
//

#include "MobiBook.h"

MobiBook::MobiBook(std::string title, std::string author) {
    title_ = title;
    author_ = author;
}

void MobiBook::addHtml(std::string filename) {
    std::ifstream file(filename.c_str(), std::ifstream::in);

    //file.
    html_content_.append(filename);
}