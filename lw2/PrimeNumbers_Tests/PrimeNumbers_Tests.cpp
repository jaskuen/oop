#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"
#include "../PrimeNumbers/Prime.h"
#include <iostream>

using Set = std::set<int>;

SCENARIO("UPPER < 0")
{
	Set set = GeneratePrimeNumbersSet(-100);
	REQUIRE(set.size() == 0);
}

SCENARIO("UPPER = O")
{
	Set set = GeneratePrimeNumbersSet(0);
	REQUIRE(set.size() == 0);
}

SCENARIO("UPPER = 1, 1 IS NOT PRIME")
{
	Set set = GeneratePrimeNumbersSet(1);
	REQUIRE(set.size() == 0);
}

SCENARIO("UPPER = 2, IS ONLY PRIME HERE")
{
	Set set = GeneratePrimeNumbersSet(2);
	REQUIRE(set.size() == 1);
	REQUIRE(set.find(2) != set.cend());
}	

SCENARIO("UPPER = 3, PRIMES ARE 2, 3")
{
	Set set = GeneratePrimeNumbersSet(3);
	REQUIRE(set.size() == 2);
	REQUIRE(set.find(2) != set.cend());
	REQUIRE(set.find(3) != set.cend());
}

SCENARIO("UPPER = 100000000, COUNT OF PRIMES IS 5761455, LESS THAN 12 SEC")
{
	auto start = clock();
	Set set = GeneratePrimeNumbersSet(100000000);
	auto end = clock();
	REQUIRE(set.size() == 5761455);
	REQUIRE(end - start < 12000);
}
