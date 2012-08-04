//
//  ExthHeader.cpp
//  MobiWriter
//

#include "ExthHeader.h"

ExthHeader::ExthHeader() {
    size_ = static_cast<unsigned int>(sizeof(exth_header_));
}

bool ExthHeader::generate() {
    try {
        memset(reinterpret_cast<char *>(&exth_header_), 0, sizeof(exth_header_));

        Utils::stringToBytes("EXTH", exth_header_.identifier);
        Utils::uintToBytes(size_, exth_header_.header_length);
        Utils::uintToBytes(static_cast<unsigned int>(records_.size()), exth_header_.record_count);
        
        data_ = Utils::bytesToString(reinterpret_cast<char *>(&exth_header_), sizeof(exth_header_));
        
        for (int i = 0; i < records_.size(); ++i) {
            data_.append(records_[i]);
        }
        
        unsigned int padding = 4 - (data_.size() % 4);
        data_.resize(data_.size() + padding);
        
        if (data_.size() != size_ + padding) {
            return false;
        }
    } catch (...) {
        data_ = "";
        return false;
    }
    
    return true;
}

void ExthHeader::addRecord(ExthRecordType type, std::string data) {
    ExthRecordStruct record;
    Utils::uintToBytes(type, record.type);
    Utils::uintToBytes(static_cast<unsigned int>(data.size() + sizeof(record)), record.length);
    
    std::string record_string = Utils::bytesToString(reinterpret_cast<char *>(&record), sizeof(record));
    record_string.append(data);
    
    size_ += record_string.size();
    records_.push_back(record_string);
}
