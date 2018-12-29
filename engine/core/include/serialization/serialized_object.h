#include <utility>

#ifndef SHIROIENGINE_SERIALIZED_OBJECT_H
#define SHIROIENGINE_SERIALIZED_OBJECT_H

#include <string>
#include <vector>
#include <types.h>

struct SerializedMember {
private:
    std::string name;
    // We use bytes to we can manipulate memory easier
    uint8 *ptr;
    size_t size;
public:
    template<typename T>
    SerializedMember(std::string name, T &value) : name(std::move(name)), ptr(nullptr), size(0) {
        size = sizeof(T);
        ptr = (uint8 *) malloc(size);
        *(ptr) = value;
    }

    SerializedMember(const std::string &name, uint8 *ptr, size_t size) : name(name), ptr(ptr), size(size) {}

    ~SerializedMember() {
        delete ptr;
    }

    const std::string &getName() const {
        return name;
    }

    void *getPtr() const {
        return ptr;
    }

    size_t getSize() const {
        return size;
    }
};

#define GENERATE_PRIMITIVE_WRITE_METHOD(type) \
template<>\
void write(const std::string &name, const type &value) {\
    writeInternal(name, value);\
}

class SerializedObject {
private:
    std::vector<SerializedObject> children;
    std::vector<SerializedMember *> members;
public:
    template<typename T>
    void write(const std::string &name, const T &value) {
        static_assert(false,
                      "You can only use \"write<T>\" with primitive types! For complex objects, create a new serialized object")
    }

    template<typename T>
    T extract(const std::string &name) {
        for (SerializedMember &member : members) {
            if (member.getName() == name) {
                assert(member.getSize() == sizeof(T));
                return (T) *((T *) member.getPtr());
            }

        }
        throw std::runtime_error(std::string("Property '") + name + "' not found.");
    }

    GENERATE_PRIMITIVE_WRITE_METHOD(float32)

    GENERATE_PRIMITIVE_WRITE_METHOD(float64)

    GENERATE_PRIMITIVE_WRITE_METHOD(uint8)

    GENERATE_PRIMITIVE_WRITE_METHOD(uint16)

    GENERATE_PRIMITIVE_WRITE_METHOD(uint32)

    GENERATE_PRIMITIVE_WRITE_METHOD(uint64)

    GENERATE_PRIMITIVE_WRITE_METHOD(int8)

    GENERATE_PRIMITIVE_WRITE_METHOD(int16)

    GENERATE_PRIMITIVE_WRITE_METHOD(int32)

    GENERATE_PRIMITIVE_WRITE_METHOD(int64)

    template<>
    void write(const std::string &name, const std::string &value) {
        auto ptr = (uint8 *) malloc(sizeof(uint8) * value.size());

        for (int i = 0; i < value.size(); ++i) {
            *(ptr + i) = value[i];
        }
        members.push_back(new SerializedMember(name, ptr, value.size()));
    }

    ~SerializedObject() {
        for (auto member : members) {
            delete member;
        }
    }

private:
    template<typename T>
    void writeInternal(std::string name, T &value) {
        members.push_back(new SerializedMember(name, value));
    }
};

class ISerializable {
    virtual void serialize(SerializedObject object) = 0;
};

#endif
