//
//  MobiWriter.cpp
//  MobiWriter
//

#include "MobiWriter.h"

bool MobiWriter::write(MobiBook *mobi_book, std::string filename) {
    for (size_t i = 0; i < mobi_book->html_content().size(); i += 4096) {
        text_records_.push_back(mobi_book->html_content().substr(i, 4096) + '\0');
    }
    
    PalmDatabaseHeader palm_database_header = PalmDatabaseHeader(static_cast<unsigned int>(text_records_.size() + 2));
    PalmDocHeader palm_doc_header = PalmDocHeader();
    MobiHeader mobi_header = MobiHeader();
    ExthHeader exth_header = ExthHeader();
    EofRecord eof_record = EofRecord();

    exth_header.addRecord(AUTHOR, mobi_book->author());
    
    if (!exth_header.generate()) {
        std::cout << "error creating the exth header" << std::endl;
        return false;
    }
    
    if (!palm_doc_header.generate(static_cast<unsigned int>(mobi_book->html_content().size()),
                                  static_cast<unsigned int>(text_records_.size()))) {
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
    
    std::string record0 = palm_doc_header.data() + mobi_header.data() + exth_header.data();
        
    std::string book_title_padded = mobi_book->title();
    size_t book_title_padding = Utils::getFourBytesPadding(book_title_padded.size() + 2);
    book_title_padded.resize(book_title_padded.size() + book_title_padding + 2);
    
    record0.append(book_title_padded);
    
    std::vector<std::string> records;
    records.push_back(record0);
    
    
    for (int i = 0; i < text_records_.size(); ++i) {
        records.push_back(text_records_[i]);
    }
    
    if (!eof_record.generate()) {
        std::cout << "error generating the eof record" << std::endl;
        return false;
    }
    
    records.push_back(eof_record.data());
    
    if (!palm_database_header.generate(mobi_book->title(), records)) {
        std::cout << "error generating the palm database header";
        return false;
    }
    
    std::ofstream file(filename.c_str(), std::ios::out);
    
    file << palm_database_header.data();
    
    for (int i = 0; i < records.size(); ++i) {
        file << records[i];
    }
    
    file.close();
    
    return true;
}
