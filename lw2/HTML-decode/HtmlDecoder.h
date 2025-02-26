#pragma once
#include <string>
#include <map>

const std::map<std::string, char> ENTITY_TO_CHAR
{
    {"&quot;", '"'},
    {"&apos;", '\''},
    {"&lt;", '<'},
    {"&gt;", '>'},
    {"&amp;", '&'},
};

std::string HtmlDecode(const std::string& html);
