#include "URL-parser.h"
#include "URL-parser-tools.h"

#include <string>
#include <algorithm>
#include <cctype>

void RegexMatch(std::smatch& matches, const std::string& url)
{
    const std::regex urlPattern("^(http[s]?|ftp)://([^:/]+)(?::(\\d+))?(?:/(.*))?$", std::regex::icase);
    std::regex_match(url, matches, urlPattern);
}

void SetBasePort(const Protocol& protocol, int& port)
{
    if (protocol == Protocol::HTTP)
    {
        port = 80;
    }
    else if (protocol == Protocol::HTTPS)
    {
        port = 443;
    }
    else if (protocol == Protocol::FTP)
    {
        port = 21;
    }
    else 
    {
        port = -1;
    }
}

void ParseRegexPort(const std::ssub_match& unparsedRegex, int& port)
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

bool ParseProtocol(const std::ssub_match& regexProtocol, Protocol& protocol)
{
    std::string protocolStr = regexProtocol;
    std::string lowerProtocol;
    lowerProtocol.resize(protocolStr.length());
    std::transform(protocolStr.begin(), protocolStr.end(), lowerProtocol.begin(), ::tolower);

    if (lowerProtocol == "http")
    {
        protocol = Protocol::HTTP;
    }
    else if (lowerProtocol == "https")
    {
        protocol = Protocol::HTTPS;
    }
    else if (lowerProtocol == "ftp")
    {
        protocol = Protocol::FTP;
    }
    else
    {
        return false;
    }

    return true;
}

bool ParsePort(Protocol& protocol, const std::ssub_match& regexPort, int& port)
{
    SetBasePort(protocol, port);
    if (regexPort.matched)
    {
        ParseRegexPort(regexPort, port);
    }
    if (port == -1)
    {
        return false;
    }
    return true;
}

bool ParseHost(const std::ssub_match& regexHost, std::string& host)
{
    host = regexHost;
    if (host.empty())
    {
        return false;
    }
    return true;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document) 
{
    std::smatch matches;
    RegexMatch(matches, url);

    if (!matches.ready())
    {
        return false;
    }

    if (!ParseProtocol(matches[1], protocol))
    {
        return false;
    }
    
    if (!ParseHost(matches[2], host))
    {
        return false;
    }

    if (!ParsePort(protocol, matches[3], port))
    {
        return false;
    }

    document = matches[4].matched ? matches[4] : std::string();
    return true;
}