//
//  MobiWriter.cpp
//  MobiWriter
//

#include "MobiWriter.h"

bool MobiWriter::write(MobiBook *mobi_book, std::string filename) {
    mobi_book_ = mobi_book;
        
    generateTextRecords();

    std::vector<std::string> records;
    std::string record0 = "";
    
    PalmDatabaseHeader palm_database_header = PalmDatabaseHeader(static_cast<unsigned int>(text_records_.size() + 2));
    PalmDocHeader palm_doc_header = PalmDocHeader();
    MobiHeader mobi_header = MobiHeader();
    ExthHeader exth_header = ExthHeader();
    
    exth_header.addRecord(AUTHOR, mobi_book->author());
    
    char creator_software[4];
    Utils::uintToBytes(201, creator_software);
    exth_header.addRecord(CREATOR_SOFTWARE, Utils::bytesToString(creator_software, 4));
    
    char creator_version_major[4];
    Utils::uintToBytes(1, creator_version_major);
    exth_header.addRecord(CREATOR_MAJOR_VERSION, Utils::bytesToString(creator_version_major, 4));
    
    char creator_version_minor[4];
    Utils::uintToBytes(2, creator_version_minor);
    exth_header.addRecord(CREATOR_MINOR_VERSION, Utils::bytesToString(creator_version_minor, 4));
    
    char creator_version_build[4];
    Utils::uintToBytes(33307, creator_version_build);
    exth_header.addRecord(CREATOR_BUILD_NUMBER, Utils::bytesToString(creator_version_build, 4));
    
    if (!palm_doc_header.generate(static_cast<unsigned int>(mobi_book->html_content().size()), static_cast<unsigned int>(text_records_.size()))) {
        std::cout << "error creating the palm doc header" << std::endl;
        return false;
    }
    
    if (!mobi_header.generate(65001,
                         palm_database_header.size(),
                         palm_doc_header.size(),
                         exth_header.size(),
                         static_cast<unsigned int>(mobi_book->title().size()),
                         1033,
                             text_records_.size())) {
        
        std::cout << "error creating the mobi header" << std::endl;
        return false;
    }
    
    if (!exth_header.generate()) {
        std::cout << "error creating the exth header" << std::endl;
        return false;

    }
    
    record0.append(palm_doc_header.data());
    record0.append(mobi_header.data());
    record0.append(exth_header.data());
    
    size_t book_title_padding = 4 - ((mobi_book->title().size() + 2) % 4);
    std::string book_title_padded = mobi_book->title();
    book_title_padded.resize(book_title_padded.size() + book_title_padding);
    
    record0.append(book_title_padded);
    
    records.push_back(record0);
    
    for (int i = 0; i < text_records_.size(); ++i) {
        records.push_back(text_records_[i]);
    }
    
    EofRecord eof_record = EofRecord();
    if (!eof_record.generate()) {
        std::cout << "error generating the eof record" << std::endl;
        return false;
    }
    
    records.push_back(eof_record.data());
    
    if (!palm_database_header.generate(mobi_book->title(), records)) {
        std::cout << "error generating the palm database header";
        return false;
    }
    
    FILE *f = fopen(filename.c_str(), "wb");
    fwrite(palm_database_header.data().c_str(), palm_database_header.data().size(), 1, f);
    
    for (int i = 0; i < records.size(); ++i) {
        fwrite(records[i].c_str(), records[i].size(), 1, f);
    }
    
    fclose(f);
    
    return true;
}

void MobiWriter::generateTextRecords() {
    for (size_t i = 0; i < mobi_book_->html_content().size(); i += 4096) {
        text_records_.push_back(mobi_book_->html_content().substr(i, 4096));
    }
}
