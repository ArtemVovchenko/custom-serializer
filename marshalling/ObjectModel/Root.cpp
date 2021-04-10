//
//  Root.cpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#include "Root.hpp"

namespace Objects {
    
    Root::Root()
    :
    name_("undefined"),
    wrapper_(0),
    nameLength_(0),
    size_(sizeof size_ + sizeof wrapper_ + sizeof nameLength_)
    {}
    
    
    int32_t Root::getSize() {
        return this->size_;
    }
    
    
    std::string Root::getName() {
        return this->name_;
    }
    
    
    void Root::setName(std::string name) {
        this->name_ = name;
        this->nameLength_ = (int16_t) name.length();
        this->size_ += this->nameLength_;
    }
    
}
