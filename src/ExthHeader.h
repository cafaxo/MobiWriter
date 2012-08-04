//
//  ExthHeader.h
//  MobiWriter
//

#ifndef MobiWriter_ExthHeader_h
#define MobiWriter_ExthHeader_h

#include "Utils.h"

struct ExthHeaderStruct {
    char identifier[4];
    char header_length[4];
    char record_count[4];
};

struct ExthRecordStruct {
    char type[4];
    char length[4];
};

enum ExthRecordType {
    AUTHOR = 100,
    CREATOR_SOFTWARE = 204,
    CREATOR_MAJOR_VERSION = 205,
    CREATOR_MINOR_VERSION = 206,
    CREATOR_BUILD_NUMBER = 207
};

class ExthHeader {
public:
    ExthHeader();
    void addRecord(ExthRecordType type, std::string data);
    bool generate();
    
    ExthHeaderStruct exth_header() const { return exth_header_; }
    std::string data() const { return data_; }
    unsigned int size() const { return size_; }
    
private:
    
    ExthHeaderStruct exth_header_;
    std::string data_;
    std::vector<std::string> records_;
    unsigned int size_;
};

#endif
