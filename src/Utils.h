//
//  Utils.h
//  MobiWriter
//

#ifndef MobiWriter_Utils_h
#define MobiWriter_Utils_h

#include <iostream>
#include <vector>

class Utils {
public:
    static inline unsigned short swapEndian(unsigned short x) {
        return (x >> 8) | (x << 8);
    }
    
    static inline unsigned int swapEndian(unsigned int x) {
        return (x >> 24) | ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) | (x << 24);
    }
    
    static inline void stringToBytes(std::string string, char *bytes) {
        const void *pointer = string.c_str();
        memcpy(bytes, pointer, string.size());
    }
    
    static inline void ushortToBytes(unsigned short x, char *bytes, bool swap_endian = true) {
        if (swap_endian)
            x = swapEndian(x);
        
        memcpy(bytes, reinterpret_cast<char *>(&x), sizeof(unsigned short));
    }
    
    static inline void uintToBytes(unsigned int x, char *bytes, bool swap_endian = true) {
        if (swap_endian)
            x = swapEndian(x);
        
        memcpy(bytes, reinterpret_cast<char *>(&x), sizeof(unsigned int));
    }
    
    static inline size_t getFourBytesPadding(size_t size)
    {
        int padding = 4 - (size % 4);
        
        if (padding == 4) {
            return 0;
        } else {
            return padding;
        }
    }
    
    static inline std::string bytesToString(char *bytes, size_t size) {
        std::string string = "";
        string.resize(size);
        
        for (int i = 0; i < size; ++i) {
            string[i] = bytes[i];
        }
        
        return string;
    }
};

#endif
