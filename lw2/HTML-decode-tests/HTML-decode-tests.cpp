#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../HTML-decode/HtmlDecoder.h"

SCENARIO("EMPTY STRING")
{
	std::string empty;
	std::string result = HtmlDecode(empty);
	REQUIRE(result == "");
}

SCENARIO("STRING CONTAINS ONLY &quot; ENTITY")
{
	std::string input = "&quot;";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "\"");
}

SCENARIO("STRING CONTAINS ONLY &apos; ENTITY")
{
	std::string input = "&apos;";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "\'");
}

SCENARIO("STRING CONTAINS ONLY &lt; ENTITY")
{
	std::string input = "&lt;";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "<");
}

SCENARIO("STRING CONTAINS ONLY &gt; ENTITY")
{
	std::string input = "&gt;";
	std::string result = HtmlDecode(input);
	REQUIRE(result == ">");
}

SCENARIO("STRING CONTAINS ONLY &amp; ENTITY")
{
	std::string input = "&amp;";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "&");
}

SCENARIO("EXAMPLE FROM GITHUB")
{
	std::string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("NOT USING DECODED & IN DECODING AGAIN")
{
	std::string input = "&amp;amp;";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "&amp;");
}

SCENARIO("NO ENTITIES")
{
	std::string input = "just any string without entities.";
	std::string result = HtmlDecode(input);
	REQUIRE(result == input);
}

SCENARIO("SPACE BETWEEN & AND ENTITY BODY")
{
	std::string input = "Cat & lt;says& gt; & quot;Meow& quot;. M& amp;M& apos;s";
	std::string result = HtmlDecode(input);
	REQUIRE(result == input);
}

SCENARIO("& without ;")
{
	std::string input = "just &any string without entities.";
	std::string result = HtmlDecode(input);
	REQUIRE(result == input);
}

SCENARIO("UNKNOWN ENTITY")
{
	std::string input = "just &any; string without entities.";
	std::string result = HtmlDecode(input);
	REQUIRE(result == input);
}

// Проверка на неизвестные сущности
