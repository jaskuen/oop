#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../URL-parser/URL-parser.h"
#include <string>

Protocol protocol;
int port;
std::string url, host, document;

SCENARIO("Empty URL")
{
	url = "";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

SCENARIO("Incorrect protocol")
{
	url = "htps://example.com/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

SCENARIO("Incorrect ://")
{
	url = "http:/example.com/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

SCENARIO("No host")
{
	url = "https://:8080/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

SCENARIO("Port out of range")
{
	url = "https://localhost:123456/";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(!result);
}

SCENARIO("Correct url")
{
	url = "https://example.com/docs/doc.txt";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTPS);
	REQUIRE(port == 443);
	REQUIRE(host == "example.com");
	REQUIRE(document == "docs/doc.txt");
}

SCENARIO("GitHub example")
{
	url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	bool result = ParseURL(url, protocol, port, host, document);
	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}
