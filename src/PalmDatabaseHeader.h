//
//  PalmDatabaseHeader.h
//  MobiWriter
//

#ifndef MobiWriter_PalmDatabaseHeader_h
#define MobiWriter_PalmDatabaseHeader_h

#include <ctime>
#include "Utils.h"

struct PalmDatabaseHeaderStruct {
    char name[32];
    char attributes[2];
    char version[2];
    char creation_date[4];
    char modification_date[4];
    char last_backup_date[4];
    char modification_number[4];
    char app_info_id[4];
    char sort_info_id[4];
    char type[4];
    char creator[4];
    char unique_id_seed[4];
    char next_record_list_id[4];
    char number_of_records[2];
};

struct RecordInfoStruct {
    char data_offset[4];
    char attributes[1];
    char unique_id[3];
};

class PalmDatabaseHeader {
public:
    PalmDatabaseHeader(unsigned int records_count);
    bool generate(std::string mobi_book_title, std::vector<std::string> records);
    
    PalmDatabaseHeaderStruct palm_database_header() const { return palm_database_header_; }
    std::string data() const { return data_; }
    unsigned int size() const { return size_; }
    
private:
    PalmDatabaseHeaderStruct palm_database_header_;
    std::string data_;
    unsigned int size_;
};

#endif
