#include "eOperand.hpp"

template <class T>eOperand<T>::eOperand(T data): data
{
    std::string buffer;
    if (typeid(T) == typeid(int8_t)  ||
        typeid(T) == typeid(int16_t) ||
        typeid(T) == typeid(int32_t))
        buffer = std::to_string(data);
    else if (typeid(T) == typeid(float))
    {
        //??
    }
    else if (typeid(T) == typeid(double))
    {
        // ??
    }

}