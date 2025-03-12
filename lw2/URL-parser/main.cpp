#include "URL-parser.h"
#include <iostream>
#include <string>



int main(int argc, char* argv[]) {
    try
    {
        std::string url;
        std::getline(std::cin, url);

        Protocol protocol;
        int port;
        std::string host, document;

        if (ParseURL(url, protocol, port, host, document)) {
            std::cout << url << std::endl;
            std::cout << "HOST: " << host << std::endl;
            std::cout << "PORT: " << port << std::endl;
            std::cout << "DOC: " << document << std::endl;
        }
        else {
            std::cout << "ERROR" << std::endl;
        }
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
    

}