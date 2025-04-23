#pragma once
#include <stdexcept>

class CUrlParsingError : public std::invalid_argument 
{
public:
    explicit CUrlParsingError(const std::string& what)
        : std::invalid_argument(what), what_message(what) 
    {
    }

    const char* what() const noexcept override 
    {
        return what_message.c_str();
    }

private:
    std::string what_message;
};