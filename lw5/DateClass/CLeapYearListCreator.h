#pragma once
#include <map>

const int MIN_YEAR = 1970;
const int MAX_YEAR = 9999;

static class CLeapYearListCreator
{
public:
	static std::map<int, int> Create();
};
