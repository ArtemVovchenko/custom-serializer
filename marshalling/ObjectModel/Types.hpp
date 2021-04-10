//
//  Types.hpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#ifndef Types_hpp
#define Types_hpp

#include <stdint.h>
#include <exception>

namespace Objects {
    
    enum class Wrapper : int8_t {
        PRIMITIVE = 1,
        ARRAY,
        STRING,
        OBJECT
    };
    
    enum class Type : int8_t {
        INT8 = 1,
        INT16,
        INT32,
        INT64,
        
        UINT8,
        UINT16,
        UINT32,
        UINT64,
        
        FLOAT,
        DOUBLE,
        
        BOOLEAN
    };
    
    template <typename ...>
    int8_t getTypeSize(Type type);
}



#endif /* Types_hpp */
