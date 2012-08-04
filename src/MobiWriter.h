//
//  MobiWriter.h
//  MobiWriter
//

#ifndef MobiWriter_MobiWriter_h
#define MobiWriter_MobiWriter_h

#include <vector>
#include <ctime>

#include "MobiBook.h"
#include "PalmDatabaseHeader.h"
#include "PalmDocHeader.h"
#include "MobiHeader.h"
#include "ExthHeader.h"
#include "EofRecord.h"

class MobiWriter {
public:
    bool write(MobiBook *mobi_book, std::string filename);
    
private:
    void generateTextRecords();
    
    std::vector<std::string> text_records_;
    std::string mobi_data_;
    MobiBook *mobi_book_;
};

#endif
