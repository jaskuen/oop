#include "URL-parser.h"

#include <regex>
#include <string>
#include <algorithm>
#include <cctype>

void SetProtocolAndBasePort(const std::string& strProtocol, Protocol& protocol, int& port)
{
    if (strProtocol == "http")
    {
        protocol = Protocol::HTTP;
        port = 80;
    }
    else if (strProtocol == "https")
    {
        protocol = Protocol::HTTPS;
        port = 443;
    }
    else if (strProtocol == "ftp")
    {
        protocol = Protocol::FTP;
        port = 21;
    }
    else 
    {
        port = -1;
    }
}

void ParsePort(const std::ssub_match& unparsedRegex, int& port)
{
    try
    {
        port = std::stoi(unparsedRegex);
        if (port < 1 || port > 65535)
        {
            port = -1;
            return;
        }
    }
    catch (...)
    {
        port = -1;
    }
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document) 
{
    const std::regex urlPattern("^(http|https|ftp)://([^:/]+)(?::(\\d+))?(?:/(.*))?$", std::regex::icase);

    std::smatch matches;
    if (!std::regex_match(url, matches, urlPattern))
    {
        return false;
    }

    std::string protocolStr = matches[1];
    std::string lowerProtocol;
    lowerProtocol.resize(protocolStr.length());
    std::transform(protocolStr.begin(), protocolStr.end(), lowerProtocol.begin(), ::tolower);

    SetProtocolAndBasePort(lowerProtocol, protocol, port);
    if (matches[3].matched)
    {
        ParsePort(matches[3], port);
    }
    if (port == -1)
    {
        return false;
    }

    host = matches[2];
    if (host.empty()) 
    {
        return false;
    }

    document = matches[4].matched ? matches[4] : std::string();
    return true;
}