//
//  Types.cpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#include "Types.hpp"

namespace Objects {
    
    template<typename ...>
    int8_t getTypeSize(Type type) {
        switch (type) {
            case Type::INT8:
                return sizeof(int8_t);
                break;
                
            case Type::INT16:
                return sizeof(int16_t);
                break;
                
            case Type::INT32:
                return sizeof(int32_t);
                break;
                
            case Type::INT64:
                return sizeof(int64_t);
                break;
                
            case Type::UINT8:
                return sizeof(u_int8_t);
                break;
                
            case Type::UINT16:
                return sizeof(u_int16_t);
                break;
                
            case Type::UINT32:
                return sizeof(u_int32_t);
                break;
                
            case Type::UINT64:
                return sizeof(u_int64_t);
                break;
                
            case Type::FLOAT:
                return sizeof(float);
                break;
                
            case Type::DOUBLE:
                return sizeof(double);
                break;
                
            case Type::BOOLEAN:
                return sizeof(bool);
                break;
                
        }
    }
    
}
