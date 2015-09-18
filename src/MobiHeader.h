//
//  MobiHeader.h
//  MobiWriter
//

#ifndef MobiWriter_MobiHeader_h
#define MobiWriter_MobiHeader_h

#include "Utils.h"

struct MobiHeaderStruct {
    char identifier[4];
    char header_length[4];
    char mobi_file_type[4];
    char text_encoding[4];
    char unique_id[4];
    char mobi_file_version[4];
    char orthographic_index[4];
    char inflection_index[4];
    char index_names[4];
    char index_keys[4];
    char extra_index_0[4];
    char extra_index_1[4];
    char extra_index_2[4];
    char extra_index_3[4];
    char extra_index_4[4];
    char extra_index_5[4];
    char first_non_book_index[4];
    char book_title_offset[4];
    char book_title_length[4];
    char locale[4];
    char dictionary_input_language[4];
    char dictionary_output_language[4];
    char minimum_mobipocket_version[4];
    char first_image_index[4];
    char huffman_record_offset[4];
    char huffman_record_count[4];
    char huffman_table_offset[4];
    char huffman_table_length[4];
    char exth_flags[4];
    char unknown_bytes_0[32];
    char drm_offset[4];
    char drm_count[4];
    char drm_size[4];
    char drm_flags[4];
    char unknown_bytes_1[12];
    char first_content_record_number[2];
    char last_content_record_number[2];
    char unknown_bytes_2[4];
    char fcis_record_number[4];
    char fcis_record_count[4];
    char flis_record_number[4];
    char flis_record_count[4];
    char unknown_bytes_3[8];
    char unknown_bytes_4[4];
    char unknown_bytes_5[4];
    char unknown_bytes_6[4];
    char unknown_bytes_7[4];
    char unknown_bytes_8[2];
    char traildata_flags[2];
    char first_indx_record_number[4];
};

class MobiHeader {
public:
    MobiHeader();
    bool generate(unsigned int text_encoding,
                  unsigned int palm_database_header_length,
                  unsigned int palm_doc_header_length,
                  unsigned int exth_header_length,
                  unsigned int book_title_length,
                  unsigned int locale,
                  unsigned short text_records_count);
    
    MobiHeaderStruct mobi_header() const { return mobi_header_; }
    std::string data() const { return data_; }
    unsigned int size() const { return size_; }
    
private:
    MobiHeaderStruct mobi_header_;
    std::string data_;
    unsigned int size_;
};

#endif
