//
//  PalmDatabaseHeader.cpp
//  MobiWriter
//

#include "PalmDatabaseHeader.h"

PalmDatabaseHeader::PalmDatabaseHeader(unsigned int records_count) {
    size_ = static_cast<unsigned int>(sizeof(palm_database_header_) + (records_count * 8) + 2);
}

bool PalmDatabaseHeader::generate(std::string mobi_book_title, std::vector<std::string> records) {
    memset(reinterpret_cast<char *>(&palm_database_header_), 0, sizeof(palm_database_header_));

    try {
        Utils::stringToBytes(mobi_book_title, palm_database_header_.name);
        
        unsigned int timestamp = static_cast<unsigned int>(time(NULL));        
        Utils::uintToBytes(timestamp, palm_database_header_.creation_date);
        Utils::uintToBytes(timestamp, palm_database_header_.modification_date);
        
        Utils::stringToBytes("BOOK", palm_database_header_.type);
        Utils::stringToBytes("MOBI", palm_database_header_.creator);
        
        Utils::ushortToBytes(records.size(), palm_database_header_.number_of_records);
        
        data_ = Utils::bytesToString(reinterpret_cast<char *>(&palm_database_header_), sizeof(palm_database_header_));
        unsigned int record_data_offset = static_cast<unsigned int>(sizeof(palm_database_header_) + (records.size() * 8) + 2);
        
        for (int i = 0; i < records.size(); ++i) {
            RecordInfoStruct record_info_struct;
            memset(reinterpret_cast<char *>(&record_info_struct), 0, sizeof(record_info_struct));
            
            Utils::uintToBytes(record_data_offset, record_info_struct.data_offset);
            record_data_offset += records[i].size();
            
            // TODO: define attribute and unique id
            
            data_.append(Utils::bytesToString(reinterpret_cast<char *>(&record_info_struct), sizeof(record_info_struct)));
        }
        
        data_.resize(data_.size() + 2);
        
        if (data_.size() != size_) {
            return false;
        }
    } catch (...) {
        data_ = "";
        return false;
    }

    return true;
}
