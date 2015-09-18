//
//  MobiHeader.cpp
//  MobiWriter
//

#include "MobiHeader.h"

MobiHeader::MobiHeader() {
    size_ = static_cast<unsigned int>(sizeof(mobi_header_));
}

bool MobiHeader::generate(unsigned int text_encoding,
                          unsigned int palm_database_header_length,
                          unsigned int palm_doc_header_length,
                          unsigned int exth_header_length,
                          unsigned int book_title_length,
                          unsigned int locale,
                          unsigned short text_records_count) {
    memset(reinterpret_cast<char *>(&mobi_header_), 0, sizeof(mobi_header_));
    
    try {
        Utils::stringToBytes("MOBI", mobi_header_.identifier);
        Utils::uintToBytes(size_, mobi_header_.header_length);
        Utils::uintToBytes(2, mobi_header_.mobi_file_type);
        
        Utils::uintToBytes(text_encoding, mobi_header_.text_encoding);
        Utils::uintToBytes(8496792470, mobi_header_.unique_id); // TODO: get correct random id here
        Utils::uintToBytes(5, mobi_header_.mobi_file_version); // TODO: verify this value
        
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.orthographic_index, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.inflection_index, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.orthographic_index, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.index_names, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.index_keys, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.extra_index_0, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.extra_index_1, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.extra_index_2, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.extra_index_3, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.extra_index_4, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.extra_index_5, false);
        
        Utils::uintToBytes(text_records_count + 1, mobi_header_.first_non_book_index); // TODO: verify this value
        
        unsigned int book_title_offset = palm_doc_header_length
                                       + static_cast<unsigned int>(sizeof(mobi_header_))
                                       + exth_header_length;
        
        Utils::uintToBytes(book_title_offset, mobi_header_.book_title_offset); // TODO: verify book title offset
        Utils::uintToBytes(book_title_length, mobi_header_.book_title_length);
        
        Utils::uintToBytes(locale, mobi_header_.locale);
        
        Utils::uintToBytes(6, mobi_header_.minimum_mobipocket_version);
        
        Utils::uintToBytes(0b1010000, mobi_header_.exth_flags, true);
        
        Utils::uintToBytes(text_records_count + 1, mobi_header_.first_image_index); // TODO: verify first image index
        
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.drm_offset, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.drm_count, false);
        
        Utils::ushortToBytes(1, mobi_header_.first_content_record_number);
        Utils::ushortToBytes(text_records_count, mobi_header_.last_content_record_number);  // TODO: verify last content record number
        
        Utils::uintToBytes(0x00000001, mobi_header_.unknown_bytes_2, false);
        
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.fcis_record_number); // TODO: verify fcis record number
        Utils::uintToBytes(0x00000000, mobi_header_.fcis_record_count, false);
        
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.flis_record_number); // TODO: verify flis record number
        Utils::uintToBytes(0x00000000, mobi_header_.flis_record_count, false);
        
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.unknown_bytes_4, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.unknown_bytes_6, false);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.unknown_bytes_7, false);
        Utils::ushortToBytes(0x0000, mobi_header_.unknown_bytes_8, false);
        Utils::ushortToBytes(1, mobi_header_.traildata_flags, true);
        Utils::uintToBytes(0xFFFFFFFF, mobi_header_.first_indx_record_number, false);
        
        data_ = Utils::bytesToString(reinterpret_cast<char *>(&mobi_header_), sizeof(mobi_header_));
        
        if (data_.size() != size_) {
            return false;
        }
    } catch (...) {
        data_ = "";
        return false;
    }
    
    return true;
}