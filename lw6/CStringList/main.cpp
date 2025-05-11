#include <iostream>
#include "CStringList.h"

int main()
{
    CStringList list;
    list.PushBack("a");
    list.PushBack("bcd");
    list.PushBack("efghij");
    std::cout << list.Size();

    auto b = list.crbegin();
    while (b != list.crend())
    {
        std::cout << *b << std::endl;
        b++;
    }

    list.Clear();

    auto c = list.cbegin();
    while (c != list.cend())
    {
        std::cout << *c << std::endl;
        c++;
    }
}
