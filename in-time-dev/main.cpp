//
//  main.cpp
//  in-time-dev
//
//  Created by Artem Vovchenko on 09.04.2021.
//

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <stdint.h>


#pragma mark - DECLARATIONS

namespace Utils {
    template <typename T>
    void encode(std::vector<int8_t> * buffer, int16_t *iterator, T value) {
        for (int i = 0; i < sizeof value; ++i) {
            (*buffer)[(*iterator)++] = (value >> ((sizeof value * 8 - 8) - (i * 8)));
        }
    }
    
    template <>
    inline void encode<std::string>(std::vector<int8_t> * buffer, int16_t *iterator, std::string value) {
        for (unsigned int i = 0; i < value.size(); ++i) {
            encode<int8_t>(buffer, iterator, value[i]);
        }
    }
    
    template <>
    inline void encode<float>(std::vector<int8_t> * buffer, int16_t *iterator, float value) {
        int32_t bytes = *reinterpret_cast<int32_t*>(&value);
        encode(buffer, iterator, bytes);
    }
    
    template <>
    inline void encode<double>(std::vector<int8_t> * buffer, int16_t *iterator, double value) {
        int64_t bytes = *reinterpret_cast<int64_t*>(&value);
        encode(buffer, iterator, bytes);
    }
    
    template <typename T>
    void encode(std::vector<int8_t> * buffer, int16_t *iterator, std::vector<T> value) {
        for (unsigned int i = 0; i < value.size(); ++i) {
            encode<T>(buffer, iterator, value[i]);
        }
    }}

namespace Objects {
    
    // MARK: Type
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
    
    
    // MARK: Root
    class Root {
    protected:
        std::string name_;  // prim name
        int16_t nameLength_; // Length of name in bytes
        int8_t wrapper_;    // Wrapper length (1 byte)
        int32_t size_;      // All size of primitive record
        
    protected:
        Root();
        
    public:
        int32_t getSize();
        std::string getName();
        void setName(std::string);
        
        // Pure virtual
        virtual void pack(std::vector<int8_t> *, int16_t *) = 0;
//        virtual Root * unpack (const std::vector<int8_t>&) = 0;
    };
    
    
    // MARK: Primitive
    class Primitive : public Root {
    private:
        int8_t type_;
        std::vector<int8_t> *binary_;
        
    private:
        Primitive();
        
    public:
        virtual void pack(std::vector<int8_t> *buffer, int16_t *iterator);
        
        
        template<typename T>
        static Primitive * create(std::string name, Type type, T value) {
            Primitive * p = new Primitive();
            p->setName(name);
            p->wrapper_ = static_cast<int8_t>(Wrapper::PRIMITIVE);
            p->type_ = static_cast<int8_t>(type);
            p->binary_ = new std::vector<int8_t>(sizeof value);
            p->size_ += p->binary_->size();
            
            int16_t iterator = 0;
            Utils::template encode<T>(p->binary_, &iterator, value);
            
            return p;
        }
        
        // TODO: Manage unpacking
//        virtual Root * unpack(const std::vector<int8_t> &); // is it normal to polymorphism??
    };
    
    
    //MARK: Array
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
            Utils::template encode<T>(arr->binary_, &iterator, value);
            
            return arr;
        }
        
        template <typename T>
        static Array * createString(std::string name, Type type, std::vector<T> value) {
            Array *arr = new Array();
            arr->setName(name);
            arr->count_ = static_cast<int32_t>(value.size());
            arr->type_ = static_cast<int8_t>(type);
            arr->wrapper_ = static_cast<int8_t>(Wrapper::STRING);
            arr->binary_ = new std::vector<int8_t>(sizeof(T) * arr->count_);
            arr->size_ += arr->binary_->size();
            
            int16_t iterator = 0;
            Utils::template encode<T>(arr->binary_, &iterator, value);
            
            return arr;
        }
    };
}




#pragma mark - REALIZATIONS



/// MSUT BE IN .H FILE
namespace Utils {
    
    
    /// MSUT BE IN .H FILE
}


namespace Objects {
    
    // MARK: Type
    template<typename ...>
    int8_t getTypeSize(Type type) {
        switch (type) {
                
            case Type::INT8:
                return sizeof(int8_t);
                break;
                
            case Type::INT16:
                return sizeof(int16_t);
                break;
                
            case Type::INT32:
                return sizeof(int32_t);
                break;
                
            case Type::INT64:
                return sizeof(int64_t);
                break;
                
            case Type::UINT8:
                return sizeof(u_int8_t);
                break;
                
            case Type::UINT16:
                return sizeof(u_int16_t);
                break;
                
            case Type::UINT32:
                return sizeof(u_int32_t);
                break;
                
            case Type::UINT64:
                return sizeof(u_int64_t);
                break;
                
            case Type::FLOAT:
                return sizeof(float);
                break;
                
            case Type::DOUBLE:
                return sizeof(double);
                break;
                
            case Type::BOOLEAN:
                return sizeof(bool);
                break;
                
        }
    }
    
    
    // MARK: Root
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
    
    //MARK: Primitive
    
    Primitive::Primitive() {
        size_ += sizeof type_;
    }
    
    void Primitive::pack(std::vector<int8_t> * buffer, int16_t * iterator) {
        Utils::encode<int8_t>(buffer, iterator, wrapper_); // 1 byte
        Utils::encode<int16_t>(buffer, iterator, nameLength_); // 2 bytes
        Utils::encode<std::string>(buffer, iterator, name_); // nameLen Bytes;
        Utils::encode<int8_t>(buffer, iterator, type_);
        Utils::encode<int8_t>(buffer, iterator, *binary_);
        Utils::encode<int32_t>(buffer, iterator, size_);
    }
    
    
    // MARK: Array
    
    Array::Array() {
        size_ += sizeof type_ + sizeof count_;
    }
    
    void Array::pack(std::vector<int8_t> *buffer, int16_t *iterator) {
        Utils::encode<int8_t>(buffer, iterator, wrapper_);
        Utils::encode<int16_t>(buffer, iterator, nameLength_);
        Utils::encode<std::string>(buffer, iterator, name_);
        Utils::encode<int8_t>(buffer, iterator, type_);
        Utils::encode<int32_t>(buffer, iterator, count_);
        Utils::encode<int8_t>(buffer, iterator, *binary_);
        Utils::encode<int32_t>(buffer, iterator, size_);
    }
    

}

int main(int argc, const char * argv[]) {

//    Object::Primitive *p = Object::Primitive::create<double>("int", Object::Type::DOUBLE, 12.64);
    Objects::Array *a = Objects::Array::createString<char>("str", Objects::Type::INT8, std::vector<char>{'a', 'b', 'c'});
    std::vector<int8_t> b(a->getSize());
    int16_t iter = 0;
    a->pack(&b, &iter);
    
    return 0;
}
