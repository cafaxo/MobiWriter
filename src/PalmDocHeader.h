//
//  PalmDocHeader.h
//  MobiWriter
//

#ifndef MobiWriter_PalmDocHeader_h
#define MobiWriter_PalmDocHeader_h

#include "Utils.h"

struct PalmDocHeaderStruct {
    char compression[2];
    char unused[2];
    char text_length[4];
    char text_record_count[2];
    char text_max_record_size[2];
    char current_position[4];
};

class PalmDocHeader {
public:
    PalmDocHeader();
    bool generate(unsigned int text_size, unsigned short text_record_count);
    
    PalmDocHeaderStruct palm_doc_header() const { return palm_doc_header_; }
    std::string data() const { return data_; }
    unsigned int size() const { return size_; }
    
private:
    PalmDocHeaderStruct palm_doc_header_;
    std::string data_;
    unsigned int size_;
};

#endif
