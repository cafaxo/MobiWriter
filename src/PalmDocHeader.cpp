//
//  PalmDocHeader.cpp
//  MobiWriter
//

#include "PalmDocHeader.h"

PalmDocHeader::PalmDocHeader() {
    size_ = static_cast<unsigned int>(sizeof(palm_doc_header_));
}

bool PalmDocHeader::generate(unsigned int text_size, unsigned short text_record_count) {
    try {
        memset(reinterpret_cast<char *>(&palm_doc_header_), 0, sizeof(palm_doc_header_));
        
        Utils::ushortToBytes(1, palm_doc_header_.compression);
        
        Utils::uintToBytes(text_size, palm_doc_header_.text_length);
        Utils::ushortToBytes(text_record_count, palm_doc_header_.text_record_count);
        Utils::ushortToBytes(4096, palm_doc_header_.text_max_record_size);
        
        Utils::uintToBytes(0, palm_doc_header_.current_position); // writing 0 here seems to be valid
        
        data_ = Utils::bytesToString(reinterpret_cast<char *>(&palm_doc_header_), sizeof(palm_doc_header_));
        
        if (data_.size() != size_) {
            return false;
        }
    } catch (...) {
        data_ = "";
        return false;
    }
    
    return true;
}
