#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <iostream>

#include "../DateClass/CDate.h"

// isValid method tests

SCENARIO("INVALID DATE")
{
	CDate dateOverflowMin(1, static_cast<Month>(1), 1);
	CDate dateOverflowMax(99, static_cast<Month>(99), 10000);

	bool res = dateOverflowMin.IsValid();

	REQUIRE_FALSE(dateOverflowMin.IsValid());
	REQUIRE_FALSE(dateOverflowMax.IsValid());
}

SCENARIO("VALID DATE")
{
	CDate dateMin(1, Month::JANUARY, 1970);
	CDate dateMax(31, Month::DECEMBER, 9999);
	CDate dateOfBirth(17, Month::JANUARY, 2006);

	REQUIRE(dateMin.IsValid());
	REQUIRE(dateMax.IsValid());
	REQUIRE(dateOfBirth.IsValid());
}

SCENARIO("LEAP YEAR FEBRUARY")
{
	CDate leapYear(29, Month::FEBRUARY, 1972);
	CDate nonLeapYear(29, Month::FEBRUARY, 1970);

	REQUIRE(leapYear.IsValid());
	REQUIRE_FALSE(nonLeapYear.IsValid());
}