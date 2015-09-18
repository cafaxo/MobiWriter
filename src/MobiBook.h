//
//  MobiBook.h
//  MobiWriter
//

#ifndef MobiWriter_MobiBook_h
#define MobiWriter_MobiBook_h

#include <iostream>
#include <fstream>

class MobiBook {
public:
    MobiBook(std::string title, std::string author);
    bool addHtmlFile(std::string filename);
    
    std::string title() const { return title_; }
    std::string author() const { return author_; }
    std::string &html_content() { return html_content_; }
    
private:
    std::string title_, author_, html_content_;
};

#endif
