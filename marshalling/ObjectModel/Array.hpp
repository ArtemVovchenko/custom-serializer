//
//  Array.hpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdint.h>
#include <string>
#include <vector>

#include "Root.hpp"
#include "Types.hpp"
#include "Utils.hpp"

namespace Objects {
    
    class Array : public Root {
    private:
        int8_t type_ = 0;
        int32_t count_ = 0;
        std::vector<int8_t> *binary_ = nullptr;
        
    private:
        Array();
        
    public:
        void pack(std::vector<int8_t> *buffer, int16_t *iterator);
        
        template <typename T>
        static Array * create(std::string name, Type type, std::vector<T> value) {
            Array *arr = new Array();
            arr->setName(name);
            arr->count_ = static_cast<int32_t>(value.size());
            arr->type_ = static_cast<int8_t>(type);
            arr->wrapper_ = static_cast<int8_t>(Wrapper::ARRAY);
            arr->binary_ = new std::vector<int8_t>(sizeof(T) * arr->count_);
            arr->size_ += arr->binary_->size();
            
            int16_t iterator = 0;
            Core::template encode<T>(arr->binary_, &iterator, value);
            
            return arr;
        }
        
        static Array * createString(std::string name, Type type, std::string value) {
            Array *arr = new Array();
            arr->setName(name);
            arr->count_ = static_cast<int32_t>(value.size());
            arr->type_ = static_cast<int8_t>(type);
            arr->wrapper_ = static_cast<int8_t>(Wrapper::STRING);
            arr->binary_ = new std::vector<int8_t>(sizeof(int8_t) * arr->count_);
            arr->size_ += arr->binary_->size();
            
            int16_t iterator = 0;
            Core::template encode<std::string>(arr->binary_, &iterator, value);
            
            return arr;
        }
    };
    ∑
}

#endif /* Array_hpp */
