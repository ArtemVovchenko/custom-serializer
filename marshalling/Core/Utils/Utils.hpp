//
//  Utils.hpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdint.h>
#include <vector>
#include <string>
#include <fstream>

#include "Root.hpp"

namespace Core {

    namespace Util {
        void saveBinary(const char *filename, std::vector<int8_t> buffer);
        std::vector<int8_t> loadBinary(const char *filename);
        void retriveObjAndSave(Objects::Root *obj);
    }

    
    template <typename T>
    void encode(std::vector<int8_t> * buffer, int16_t *iterator, T value) {
        for (int i = 0; i < sizeof value; ++i) {
            (*buffer)[(*iterator)++] = (value >> ((sizeof value * 8 - 8) - (i * 8)));
        }
    }
    
    template <>
    inline void encode<std::string>(std::vector<int8_t> * buffer, int16_t *iterator, std::string value) {
        for (unsigned int i = 0; i < value.size(); ++i) {
            encode<int8_t>(buffer, iterator, value[i]);
        }
    }
    
    template <>
    inline void encode<float>(std::vector<int8_t> * buffer, int16_t *iterator, float value) {
        int32_t bytes = *reinterpret_cast<int32_t*>(&value);
        encode(buffer, iterator, bytes);
    }
    
    template <>
    inline void encode<double>(std::vector<int8_t> * buffer, int16_t *iterator, double value) {
        int64_t bytes = *reinterpret_cast<int64_t*>(&value);
        encode(buffer, iterator, bytes);
    }
    
    template <typename T>
    void encode(std::vector<int8_t> * buffer, int16_t *iterator, std::vector<T> value) {
        for (unsigned int i = 0; i < value.size(); ++i) {
            encode<T>(buffer, iterator, value[i]);
        }
    }
    
}

#endif /* Utils_hpp */
