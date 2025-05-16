#include <iostream>
#include <list>
#include "CStringList.h"

int main()
{
    std::list<std::string> l;
    l.push_back("1");
    l.push_back("2");
    l.push_back("3");

    auto it = l.rbegin();

    CStringList list;
    list.PushBack("a");
    list.PushBack("bcd");
    list.PushBack("efghij");
    std::cout << list.Size();

    auto b = list.rbegin();
    while (b != list.rend())
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
