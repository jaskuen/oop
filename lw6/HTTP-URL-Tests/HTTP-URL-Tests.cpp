#include "../HTTP-URL/HttpUrl.h"
#include "../HTTP-URL/UrlParsingError.h"
#include "gtest/gtest.h"

class CHttpUrlTest : public testing::Test 
{
};

int main(int argc, char* argv[]) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(CHttpUrlTest, ParseUrl_ValidHttpUrl) 
{
    CHttpUrl url("http://example.com:8080/document");
    EXPECT_EQ(url.GetURL(), "http://example.com:8080/document");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/document");
}

TEST_F(CHttpUrlTest, ParseUrl_ValidHttpsUrl) 
{
    CHttpUrl url("https://example.com/document");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 443);
    EXPECT_EQ(url.GetDocument(), "/document");
    EXPECT_EQ(url.GetURL(), "https://example.com/document");
}

TEST_F(CHttpUrlTest, ParseUrl_DefaultPortHttp) 
{
    CHttpUrl url("http://example.com");
    EXPECT_EQ(url.GetURL(), "http://example.com/");
    EXPECT_EQ(url.GetPort(), 80);
}

TEST_F(CHttpUrlTest, ParseUrl_DefaultPortHttps)
{
    CHttpUrl url("https://example.com");
    EXPECT_EQ(url.GetURL(), "https://example.com/");
    EXPECT_EQ(url.GetPort(), 443);
}

TEST_F(CHttpUrlTest, ParseUrl_NoDocument) 
{
    CHttpUrl url("http://example.com/");
    EXPECT_EQ(url.GetURL(), "http://example.com/");
    EXPECT_EQ(url.GetDocument(), "/");
}

TEST_F(CHttpUrlTest, ParseUrl_InvalidProtocol) 
{
    EXPECT_THROW(CHttpUrl("ftp://example.com"), CUrlParsingError);
}

TEST_F(CHttpUrlTest, ParseUrl_EmptyUrl) 
{
    EXPECT_THROW(CHttpUrl(""), CUrlParsingError);
}

TEST_F(CHttpUrlTest, ParseUrl_InvalidDomain) 
{
    EXPECT_THROW(CHttpUrl("http:///document"), CUrlParsingError);
}

TEST_F(CHttpUrlTest, ParseUrl_PortOutOfRange) 
{
    EXPECT_THROW(CHttpUrl("http://example.com:65536"), std::invalid_argument);
    EXPECT_THROW(CHttpUrl("http://example.com:0"), std::invalid_argument);
}

TEST_F(CHttpUrlTest, ParseUrl_InvalidPort) 
{
    EXPECT_THROW(CHttpUrl("http://example.com:abc"), std::invalid_argument);
}

// Ctor with domain, document and protocol
// Wrong test input data
TEST_F(CHttpUrlTest, CHttpUrl_Ctor_DomainDocumentProtocol_Valid) 
{
    CHttpUrl url("example.com", "document", Protocol::HTTP);
    EXPECT_EQ(url.GetURL(), "http://example.com/document");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/document");
}

TEST_F(CHttpUrlTest, CHttpUrl_Ctor_DomainDocumentProtocol_AddsSlash) 
{
    CHttpUrl url("example.com", "document", Protocol::HTTPS);
    EXPECT_EQ(url.GetURL(), "https://example.com/document");
    EXPECT_EQ(url.GetDocument(), "/document");
}

TEST_F(CHttpUrlTest, CHttpUrl_Ctor_DomainDocumentProtocol_EmptyDocument) 
{
    CHttpUrl url("example.com", "", Protocol::HTTP);
    EXPECT_EQ(url.GetURL(), "http://example.com/");
    EXPECT_EQ(url.GetDocument(), "/");
}

TEST_F(CHttpUrlTest, CHttpUrl_Ctor_DomainDocumentProtocol_InvalidDomain) 
{
    EXPECT_THROW(CHttpUrl("", "document", Protocol::HTTP), CUrlParsingError);
}

// Ctor with port
TEST_F(CHttpUrlTest, CHttpUrl_Ctor_DomainDocumentProtocolPort_Valid) 
{
    CHttpUrl url("example.com", "document", Protocol::HTTP, 8080);
    EXPECT_EQ(url.GetURL(), "http://example.com:8080/document");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/document");
}

TEST_F(CHttpUrlTest, CHttpUrl_Ctor_DomainDocumentProtocolPort_DefaultPort) 
{
    CHttpUrl url("example.com", "document", Protocol::HTTPS, 443);
    EXPECT_EQ(url.GetURL(), "https://example.com/document");
    EXPECT_EQ(url.GetPort(), 443);
}

TEST_F(CHttpUrlTest, CHttpUrl_Ctor_DomainDocumentProtocolPort_PortOutOfRange) 
{
    EXPECT_THROW(CHttpUrl("example.com", "document", Protocol::HTTP, 0), std::out_of_range);
    EXPECT_THROW(CHttpUrl("example.com", "document", Protocol::HTTP, 65536), std::out_of_range);
}

// Protocol <<
TEST_F(CHttpUrlTest, CHttpUrl_ProtocolOutput) 
{
    std::ostringstream oss;
    oss << Protocol::HTTP;
    EXPECT_EQ(oss.str(), "http");
    oss.str(std::string());
    oss << Protocol::HTTPS;
    EXPECT_EQ(oss.str(), "https");
}

// Дополнить тестов, ломающих программу