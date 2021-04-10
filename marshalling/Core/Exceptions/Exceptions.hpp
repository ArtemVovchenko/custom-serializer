//
//  Exceptions.hpp
//  marshalling
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#ifndef Exceptions_hpp
#define Exceptions_hpp

#include <string>
#include <exception>

namespace Core {
    
    namespace Exeptions {
        
        class BaseException : public std::exception {
            
        protected:
            std::string message_;
            
        public:
            explicit BaseException()                       : message_("Base Exception") {}
            explicit BaseException(const char *msg)        : message_(msg) {};
            explicit BaseException(const std::string &msg) : message_(msg) {};
            
        public:
            virtual const char *what() const noexcept { return message_.c_str(); }
            
        };
        
        
        class NotImplemented : public BaseException {
            
        public:
            explicit NotImplemented() : BaseException("Not implemented") {}
        };
        
    }
}


#endif /* Exceptions_hpp */
