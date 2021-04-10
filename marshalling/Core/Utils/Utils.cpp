//
//  Utils.cpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#include "Utils.hpp"

namespace Core {
    void Util::saveBinary(const char *filename, std::vector<int8_t> buffer) {
        std::ofstream out;
        out.open(filename);
        
        for (unsigned i = 0; i < buffer.size(); ++i) {
            out << buffer[i];
        }
        out.close();
    }
    
    std::vector<int8_t> Util::loadBinary(const char *filename) {
        std::ifstream in(filename, std::ios::binary);
        
        std::vector<int8_t> result((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        return result;
    }
    
    void Util::retriveObjAndSave(Objects::Root *obj) {
        std::string name = obj->getName().append(".obin");
        std::vector<int8_t> buffer(obj->getSize());
        int16_t iterator = 0;
        
        obj->pack(&buffer, &iterator);
        saveBinary(name.c_str(), buffer);
    }
}
