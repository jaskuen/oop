#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../HTML-decode/HtmlDecoder.h"

SCENARIO("EMPTY STRING")
{
	std::string empty;
	std::string result = HtmlDecode(empty);
	REQUIRE(result == "");
}

SCENARIO("STRING CONTAINS ONLY ENTITY")
{
	bool failed = false;
	for (std::string input : {"&quot;", "&apos;", "&lt;", "&gt;", "&amp;"})
	{
		std::string result = HtmlDecode(input);
		failed = result != std::format("{}", ENTITY_TO_CHAR.at(input));
		if (failed)
		{
			break;
		}
	}
	REQUIRE(!failed);
}

SCENARIO("EXAMPLE FROM GITHUB")
{
	std::string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("NO USING DECODED & IN DECODING AGAIN")
{
	std::string input = "&amp;amp;";
	std::string result = HtmlDecode(input);
	REQUIRE(result == "&amp;");
}
