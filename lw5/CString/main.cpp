#include "CMyString.h"
#include <iostream>

int main()
{
    CMyString str1, str2;
    std::cin >> str1 >> str2;
    str1 += str2;
    str1 += str2;
    return EXIT_SUCCESS;
}
