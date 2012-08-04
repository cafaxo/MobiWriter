//
//  EofRecord.h
//  MobiWriter
//

#ifndef MobiWriter_EofRecord_h
#define MobiWriter_EofRecord_h

#include "Utils.h"

class EofRecord {
public:
    EofRecord();
    bool generate();
    
    std::string data() const { return data_; }
    unsigned int size() const { return size_; }
    
private:
    std::string data_;
    unsigned int size_;
};

#endif
