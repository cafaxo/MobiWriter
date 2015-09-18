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
        char creator_software[4];
        Utils::uintToBytes(201, creator_software);
        addRecord(CREATOR_SOFTWARE, Utils::bytesToString(creator_software, 4));
        
        char creator_version_major[4];
        Utils::uintToBytes(1, creator_version_major);
        addRecord(CREATOR_MAJOR_VERSION, Utils::bytesToString(creator_version_major, 4));
        
        char creator_version_minor[4];
        Utils::uintToBytes(2, creator_version_minor);
        addRecord(CREATOR_MINOR_VERSION, Utils::bytesToString(creator_version_minor, 4));
        
        char creator_version_build[4];
        Utils::uintToBytes(33307, creator_version_build);
        addRecord(CREATOR_BUILD_NUMBER, Utils::bytesToString(creator_version_build, 4));
        
        memset(reinterpret_cast<char *>(&exth_header_), 0, sizeof(exth_header_));

        Utils::stringToBytes("EXTH", exth_header_.identifier);
        Utils::uintToBytes(size_, exth_header_.header_length);
        Utils::uintToBytes(static_cast<unsigned int>(records_.size()), exth_header_.record_count);
        
        data_ = Utils::bytesToString(reinterpret_cast<char *>(&exth_header_), sizeof(exth_header_));
        
        for (int i = 0; i < records_.size(); ++i) {
            data_.append(records_[i]);
        }
        
        size_t padding = Utils::getFourBytesPadding(data_.size());
        data_.resize(data_.size() + padding);
        
        size_ += padding;
        
        if (data_.size() != size_) {
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
