//
//  Object.cpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#include "Object.hpp"

namespace Objects {
    
    Object::Object(std::string name) {
        setName(name);
        wrapper_ = static_cast<int8_t>(Wrapper::OBJECT);
        size_ += sizeof count_;
    }
    
    void Object::addEntity(Root *entity) {
        this->entities_.push_back(entity);
        count_ += 1;
        size_ += entity->getSize();
    }
    
    Root * Object::findEntityByName(std::string name) {
        for (auto ent : this->entities_) {
            if (ent->getName() == name) {
                return ent;
            }
        }
        return nullptr;
    }
    
    void Object::pack(std::vector<int8_t> *buffer, int16_t *iterator) {
        Core::encode<int8_t>(buffer, iterator, wrapper_);
        Core::encode<int16_t>(buffer, iterator, nameLength_);
        Core::encode<std::string>(buffer, iterator, name_);
        Core::encode<int32_t>(buffer, iterator, count_);
        
        for (auto ent : entities_) {
            ent->pack(buffer, iterator);
        }
        
        Core::encode<int32_t>(buffer, iterator, size_);
    }
    
}


