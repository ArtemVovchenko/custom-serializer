//
//  Primitive.hpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#ifndef Primitive_hpp
#define Primitive_hpp

#include <stdint.h>
#include <string>
#include <vector>

#include "Types.hpp"
#include "Root.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"

namespace Objects {
    
    class Primitive : public Root {
    private:
        int8_t type_ = 0;
        std::vector<int8_t> *binary_ = nullptr;
        
    private:
        Primitive();
//        virtual Root * unpack(std::vector<int8_t> * bindata);
        
    public:
        virtual void pack(std::vector<int8_t> *, int16_t *);
        
        
        template<typename T>
        static Primitive * create(std::string name, Type type, T value) {
            Primitive * p = new Primitive();
            p->setName(name);
            p->wrapper_ = static_cast<int8_t>(Wrapper::PRIMITIVE);
            p->type_ = static_cast<int8_t>(type);
            p->binary_ = new std::vector<int8_t>(sizeof value);
            p->size_ += p->binary_->size();
            
            int16_t iterator = 0;
            Core::template encode<T>(p->binary_, &iterator, value);
            
            return p;
        }
        
        // TODO: Manage unpacking routine
        // virtual Root * unpack(const std::vector<int8_t> &); // is it normal to polymorphism??
    };
    
}

#endif /* Primitive_hpp */
