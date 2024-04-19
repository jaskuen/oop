#pragma once
#include "DataElement.h"
#include <functional>
#include <map>

using ptr = std::shared_ptr<CDataElement>;

using Operation = std::function<double(ptr, ptr)>;

class OperationList
{
private:
    // Определения функций
    static double Plus(ptr arg1, ptr arg2) { return arg1->Value() + arg2->Value(); }
    static double Minus(ptr arg1, ptr arg2) { return arg1->Value() - arg2->Value(); }
    static double Multiply(ptr arg1, ptr arg2) { return arg1->Value() * arg2->Value(); }
    static double Divide(ptr arg1, ptr arg2) { return arg1->Value() / arg2->Value(); }
public:
    static inline std::map<char, Operation> OperationMap = {
            {'+', std::bind_front(Plus)},
            {'-', std::bind_front(Minus)},
            {'*', std::bind_front(Multiply)},
            {'/', std::bind_front(Divide)}
    };

    OperationList() {}
};