#include <iostream>
#include <map>
#include <string>
#include "HtmlDecoder.h"

int main()
{
    try
    {
        std::string line;
        while (std::getline(std::cin, line))
        {
            std::cout << HtmlDecode(line) << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
