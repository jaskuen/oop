#include <iostream>
#include "HttpUrl.h"

int main()
{
    while (true)
    {
        try
        {
            std::string url;
            std::cin >> url;
            if (std::cin.eof())
            {
                break;
            }

            CHttpUrl httpUrl(url);
            std::cout << "url: " << httpUrl.GetURL() << std::endl;
            std::cout << "protocol: " << httpUrl.GetProtocol() << std::endl;
            std::cout << "domain: " << httpUrl.GetDomain() << std::endl;
            std::cout << "port: " << httpUrl.GetPort() << std::endl;
            std::cout << "document: " << httpUrl.GetDocument() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
