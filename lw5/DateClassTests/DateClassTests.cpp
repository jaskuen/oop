#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <sstream>
#include <string>

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

// Constructor tests

SCENARIO("CDATE TIMESTAMP CTOR")
{
	CDate startDate(1, Month::JANUARY, 1970); // 01.01.1970
	CDate threeYearsLater(1, Month::JANUARY, 1973); // 01.01.1973

	CDate startDateTimestamp(0); 
	CDate threeYearsLaterTimestamp(365 * 3 + 1); 

	bool startEquals = startDate == startDateTimestamp;
	bool threeEquals = threeYearsLater == threeYearsLaterTimestamp;

	REQUIRE(startEquals);
	REQUIRE(threeEquals);
}

// Operator tests

SCENARIO("++")
{
	CDate startDate;
	CDate lastDate(31, Month::DECEMBER, 9999);

	startDate++;
	REQUIRE(startDate.GetDay() == 2);

	++startDate;
	REQUIRE(startDate.GetDay() == 3);

	lastDate++;
	REQUIRE_FALSE(lastDate.IsValid());

	lastDate--;
	REQUIRE_FALSE(lastDate.IsValid());
}

SCENARIO("--")
{
	CDate startDate(2);

	startDate--;
	REQUIRE(startDate.GetDay() == 2);

	--startDate;
	REQUIRE(startDate.GetDay() == 1);

	startDate--;
	REQUIRE_FALSE(startDate.IsValid());
}

SCENARIO("+=")
{
	CDate startDate;
	startDate += 365;

	REQUIRE(startDate.GetDay() == 1);
	REQUIRE(startDate.GetMonth() == Month::JANUARY);
	REQUIRE(startDate.GetYear() == 1971);
}

SCENARIO("-=")
{
	CDate startDate(365);
	startDate -= 365;

	REQUIRE(startDate.GetDay() == 1);
	REQUIRE(startDate.GetMonth() == Month::JANUARY);
	REQUIRE(startDate.GetYear() == 1970);
}

SCENARIO("+")
{
	CDate startDate;
	CDate nextYear = startDate + 365;

	REQUIRE(nextYear.GetYear() == 1971);

	CDate maxDate(31, Month::DECEMBER, 9999);
	maxDate = maxDate + 1;

	REQUIRE_FALSE(maxDate.IsValid());
}

SCENARIO("-")
{
	CDate startDate(1, Month::JANUARY, 1971);
	CDate previousYear = startDate - 365;

	int daysBetweenDates = startDate - previousYear;
	REQUIRE(daysBetweenDates == 365);

	REQUIRE(previousYear.GetYear() == 1970);

	previousYear = previousYear - 1;
	REQUIRE_FALSE(previousYear.IsValid());
}

SCENARIO("==, !=")
{
	CDate dateOfBirth(17, Month::JANUARY, 2006);
	CDate dateOfBirthCopy = dateOfBirth;

	bool equals = dateOfBirth == dateOfBirthCopy;
	bool notEquals = dateOfBirth != dateOfBirthCopy;

	REQUIRE(equals);

	REQUIRE_FALSE(notEquals);
}

SCENARIO(">, <=")
{
	CDate dateOfBirth(17, Month::JANUARY, 2006);
	CDate currentDate(9, Month::APRIL, 2025);

	bool more = currentDate > dateOfBirth;
	bool lessOrEqual = dateOfBirth <= currentDate;

	REQUIRE(more);
	REQUIRE(lessOrEqual);

	more = currentDate > currentDate;
	lessOrEqual = dateOfBirth <= dateOfBirth;

	REQUIRE_FALSE(more);
	REQUIRE(lessOrEqual);
}

SCENARIO("<, >=")
{
	CDate dateOfBirth(17, Month::JANUARY, 2006);
	CDate currentDate(9, Month::APRIL, 2025);

	bool less = currentDate < dateOfBirth;
	bool moreOrEqual = dateOfBirth >= currentDate;

	REQUIRE_FALSE(less);
	REQUIRE_FALSE(moreOrEqual);

	less = currentDate < currentDate;
	moreOrEqual = dateOfBirth >= dateOfBirth;

	REQUIRE_FALSE(less);
	REQUIRE(moreOrEqual);
}

SCENARIO("<<")
{
	CDate startDate;
	CDate dateOfBirth(17, Month::JANUARY, 2006);
	CDate invalidDate(40, static_cast<Month>(50), 60);
	std::ostringstream os;

	os << startDate;
	std::string dateStr = os.str();
	os.str("");

	REQUIRE(dateStr == "01.01.1970");

	os << dateOfBirth;
	dateStr = os.str();
	os.str("");

	REQUIRE(dateStr == "17.01.2006");

	os << invalidDate;
	dateStr = os.str();
	os.str("");

	REQUIRE(dateStr == "INVALID");
}

SCENARIO(">>")
{
	CDate startDate, dateOfBirth, invalidDate;
	std::istringstream is("17.01.2006 01.01.1970 50.60.70 01:01:1970");

	is >> dateOfBirth;

	REQUIRE(dateOfBirth.GetDay() == 17);
	REQUIRE(dateOfBirth.GetMonth() == Month::JANUARY);
	REQUIRE(dateOfBirth.GetYear() == 2006);

	is >> startDate;

	REQUIRE(startDate.GetDay() == 1);
	REQUIRE(startDate.GetMonth() == Month::JANUARY);
	REQUIRE(startDate.GetYear() == 1970);

	is >> invalidDate;

	REQUIRE_FALSE(invalidDate.IsValid());

	is >> invalidDate;

	REQUIRE_FALSE(invalidDate.IsValid());
}

// Get functions

SCENARIO("GETWEEKDAY")
{
	CDate currentDate(10, Month::APRIL, 2025);
	REQUIRE(currentDate.GetWeekDay() == WeekDay::THURSDAY);
}