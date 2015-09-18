//
//  MobiWriter.h
//  MobiWriter
//

#ifndef MobiWriter_MobiWriter_h
#define MobiWriter_MobiWriter_h

#include <fstream>
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
    std::vector<std::string> text_records_;
};

#endif
