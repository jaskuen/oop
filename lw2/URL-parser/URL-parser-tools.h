#pragma once
#include "URL-parser.h"
#include <regex>

void RegexMatch(std::smatch& matches, const std::string& url);
void SetBasePort(const Protocol& protocol, int& port);
void ParseRegexPort(const std::ssub_match& unparsedRegex, int& port);
bool ParseProtocol(const std::ssub_match& regexProtocol, Protocol& protocol);
bool ParsePort(Protocol& protocol, const std::ssub_match& regexPort, int& port);
bool ParseHost(const std::ssub_match& regexHost, std::string& host);

