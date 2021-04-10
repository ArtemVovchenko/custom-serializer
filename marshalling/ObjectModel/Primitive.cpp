//
//  Primitive.cpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#include "Primitive.hpp"

namespace Objects {
    Primitive::Primitive() {
        size_ += sizeof type_;
    }
    
    void Primitive::pack(std::vector<int8_t> * buffer, int16_t * iterator) {
        Core::encode<int8_t>(buffer, iterator, wrapper_);
        Core::encode<int16_t>(buffer, iterator, nameLength_);
        Core::encode<std::string>(buffer, iterator, name_);
        Core::encode<int8_t>(buffer, iterator, type_);
        Core::encode<int8_t>(buffer, iterator, *binary_);
        Core::encode<int32_t>(buffer, iterator, size_);
    }
    
//    Root * Primitive::unpack(std::vector<int8_t> * binadata) {
//        int32_t recordSize = 0;
//        for (uns i = binadata->size() - 1; i > binadata->size() - 5; --i) {
//            recordSize +=
//        }
//    }
}
