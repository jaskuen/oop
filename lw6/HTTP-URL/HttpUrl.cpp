#include "HttpUrl.h"

const int HTTP_BASE_PORT = 80;
const int HTTPS_BASE_PORT = 443;
const int PORT_MIN = 1;
const int PORT_MAX = 65535;

std::string StringProtocol(Protocol protocol)
{
    return protocol == Protocol::HTTP ? "http" : "https";
}

bool IsBasePort(Protocol protocol, unsigned short port)
{
    return (protocol == Protocol::HTTP && port == HTTP_BASE_PORT) || (protocol == Protocol::HTTPS && port == HTTPS_BASE_PORT);
}

std::string CHttpUrl::CreateUrl() const
{
    std::ostringstream stream;
    stream << StringProtocol(m_protocol) << "://" << m_domain;
    if (!IsBasePort(m_protocol, m_port))
    {
        stream << ":" << m_port;
    }
    stream << m_document;
    return stream.str();
}

void RegexMatch(std::smatch& matches, const std::string& url)
{
    const std::regex urlPattern("^(http[s]?)://([^:/]+)(?::(\\d+))?(?:/(.*))?$", std::regex::icase);
    if (!std::regex_match(url, matches, urlPattern))
    {
        throw CUrlParsingError("Failed to parse URL");
    }
}

void SetBasePort(const Protocol& protocol, unsigned short& port)
{
    if (protocol == Protocol::HTTP)
    {
        port = HTTP_BASE_PORT;
    }
    else if (protocol == Protocol::HTTPS)
    {
        port = HTTPS_BASE_PORT;
    }
    else
    {
        throw std::invalid_argument("Invalid protocol");
    }
}

void ParseProtocol(const std::ssub_match& regexProtocol, Protocol& protocol)
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
    else
    {
        throw CUrlParsingError("Invalid protocol");
    }
}

void ParsePort(Protocol& protocol, const std::string& portStr, unsigned short& port)
{
    SetBasePort(protocol, port);
    if (portStr.empty())
    {
        return;
    }
    try
    {
        int stoiPort = std::stoi(portStr);
        if (stoiPort < PORT_MIN || stoiPort > PORT_MAX)
        {
            throw std::out_of_range("Port is out of range");
        }
        port = static_cast<unsigned short>(stoiPort);
    }
    catch (...)
    {
        throw std::invalid_argument("Failed to parse port");
    }
}

void ParsePort(Protocol& protocol, const std::ssub_match& regexPort, unsigned short& port)
{
    std::string strPort = regexPort;
    ParsePort(protocol, strPort, port);
}

void ParseDomain(const std::ssub_match& regexDomain, std::string& domain)
{
    domain = regexDomain;
    if (domain.empty())
    {
        throw CUrlParsingError("Invalid domain");
    }
}

void ParseDomain(const std::string& inputDomain, std::string& domain)
{
    domain = inputDomain;
    if (domain.empty())
    {
        throw CUrlParsingError("Invalid domain");
    }
}

void ParseURL(const std::string& url, Protocol& protocol, unsigned short& port, std::string& domain, std::string& document)
{
    std::smatch matches;
    try
    {
        RegexMatch(matches, url);

        ParseProtocol(matches[1], protocol);
        ParseDomain(matches[2], domain);
        ParsePort(protocol, matches[3], port);
    }
    catch (const CUrlParsingError& error)
    {
        throw error;
    }

    document = "/";
    document += matches[4].matched ? matches[4] : std::string();
}

CHttpUrl::CHttpUrl(std::string const& url)
{
    ParseURL(url, m_protocol, m_port, m_domain, m_document);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
    m_protocol = protocol;
    ParseDomain(domain, m_domain);
    SetBasePort(m_protocol, m_port);
    m_document = document;
    if (m_document[0] != '/')
    {
        m_document = "/" + m_document;
    }
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
    : CHttpUrl(domain, document, protocol)
{
    if (!IsBasePort(protocol, port) && (port < PORT_MIN || port > PORT_MAX)) 
    {
        throw std::out_of_range("Port is out of range");
    }

    m_port = port;
}

std::string CHttpUrl::GetURL() const
{
    return CreateUrl();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::ostream& operator<<(std::ostream& os, const Protocol& protocol)
{
    return os << StringProtocol(protocol);
}