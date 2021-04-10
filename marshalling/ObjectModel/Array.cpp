//
//  Array.cpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#include "Array.hpp"

namespace Objects {
    
    Array::Array() {
        size_ += sizeof type_ + sizeof count_;
    }
    
    void Array::pack(std::vector<int8_t> *buffer, int16_t *iterator) {
        Core::encode<int8_t>(buffer, iterator, wrapper_);
        Core::encode<int16_t>(buffer, iterator, nameLength_);
        Core::encode<std::string>(buffer, iterator, name_);
        Core::encode<int8_t>(buffer, iterator, type_);
        Core::encode<int32_t>(buffer, iterator, count_);
        Core::encode<int8_t>(buffer, iterator, *binary_);
        Core::encode<int32_t>(buffer, iterator, size_);
    }
    
}
