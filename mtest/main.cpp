//
//  main.cpp
//  mtest
//
//  Created by Artem Vovchenko on 07.04.2021.
//

#include <iostream>
#include <vector>
#include "marshalling.hpp"


int main(int argc, const char * argv[]) {
    Objects::Primitive p = * Objects::Primitive::create("int", Objects::Type::INT8, 12);
    Objects::Array arr = * Objects::Array::createString("string", Objects::Type::INT8, "The C++ Is Cool Language");
    
    Core::Util::retriveObjAndSave(&p);
    Core::Util::retriveObjAndSave(&arr);
    return 0;
}
