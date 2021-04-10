//
//  Object.hpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdint.h>
#include <vector>

#include "Root.hpp"
#include "Types.hpp"
#include "Utils.hpp"

namespace Objects {
    
    class Object : public Root {
        
    private:
        std::vector<Root*> entities_;
        int16_t count_;
        
    public:
        Object(std::string name);
        
    public:
        void addEntity(Root *entity);
        Root * findEntityByName(std::string name);
        void pack(std::vector<int8_t> *buffer, int16_t *iterator);
    };
    
}

#endif /* Object_hpp */
