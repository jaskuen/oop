#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Vector/WorkWithVector.h"
#include <vector>
#include <sstream>

using DoubleVector = std::vector<double>;

SCENARIO("No numbers in input")
{
	DoubleVector array;
	std::istringstream in("");
	ReadVectorFromIstream(array, in);
	REQUIRE(array.size() == 0);
}

SCENARIO("Check if number is read correctly")
{
	DoubleVector array;
	std::istringstream in("1.22");
	ReadVectorFromIstream(array, in);
	REQUIRE(array[0] == 1.22);
}

SCENARIO("Check if average of positive is zero, if there are no positive elements")
{
	DoubleVector array{ -1.23, -45.67, -0.89 };
	DoubleVector oldArray = array;
	AddAverageOfPositiveToEachElement(array);
	REQUIRE(array == oldArray);
}

// Пустой вектор обрабатываем

SCENARIO("Check if average is a single positive number, that exists in array")
{
	DoubleVector array{ -1.23, 1.23, -2.24 };
	DoubleVector expectedArray{ 0, 2.46, -1.01 };
	AddAverageOfPositiveToEachElement(array);
	REQUIRE(array.size() == expectedArray.size());
	for (size_t i = 0; i < array.size(); ++i)
		REQUIRE(array[i] == Approx(expectedArray[i]));
	// создать второй вектор с Approax (почитать)
}

SCENARIO("Check if there are more than one positive number")
{
	DoubleVector array{ 1.2, 2.4, 4.8, -10, 0 }; // average is (1.2 + 2.4 + 4.8) / 3 = 2.8
	DoubleVector expectedArray{ 4, 5.2, 7.6, -7.2, 2.8 };
	AddAverageOfPositiveToEachElement(array);
	REQUIRE(array.size() == expectedArray.size());
	for (size_t i = 0; i < array.size(); ++i)
		REQUIRE(array[i] == Approx(expectedArray[i]));
	// ВЫнести в функцию создание вектора с Appro0x
}






