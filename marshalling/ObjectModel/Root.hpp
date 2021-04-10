//
//  Root.hpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#ifndef Root_hpp
#define Root_hpp

#include <stdint.h>
#include <string>
#include <vector>

namespace Objects {
    class Root {
    protected:
        std::string name_;
        int16_t nameLength_;
        int8_t wrapper_;
        int32_t size_;
        
    protected:
        Root();
//        virtual Root * unpack(std::vector<int8_t> *) = 0;
        
    public:
        int32_t getSize();
        std::string getName();
        void setName(std::string);
        
        // Pure virtual
        virtual void pack(std::vector<int8_t> *, int16_t *) = 0;
        //virtual Root * unpack (const std::vector<int8_t>&) = 0; // TODO: Handle unpack routine
    };
}

#endif /* Root_hpp */
