//
//  EofRecord.cpp
//  MobiWriter
//

#include "EofRecord.h"

EofRecord::EofRecord() {
    size_ = 4;
}

bool EofRecord::generate() {
    try {
        char fixed_bytes[4];
        
        fixed_bytes[0] = 0xe9;
        fixed_bytes[1] = 0x8e;
        fixed_bytes[2] = 0x0d;
        fixed_bytes[3] = 0x0a;
        
        data_ = Utils::bytesToString(fixed_bytes, 4);
    } catch (...) {
        data_ = "";
        return false;
    }
    
    return true;
}