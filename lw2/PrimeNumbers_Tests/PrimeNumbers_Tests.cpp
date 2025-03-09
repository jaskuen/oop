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
	Set set{2};
	REQUIRE(GeneratePrimeNumbersSet(2) == set);
}	

SCENARIO("UPPER = 3, PRIMES ARE 2, 3")
{
	Set set{ 2, 3 };
	REQUIRE(GeneratePrimeNumbersSet(3) == set);
}

SCENARIO("UPPER = 9, PRIMES ARE 2, 3, 5, 7")
{
	Set set{ 2, 3, 5, 7 };
	REQUIRE(GeneratePrimeNumbersSet(9) == set);
}

SCENARIO("UPPER = 11, PRIMES ARE 2, 3, 5, 7, 11")
{
	Set set{ 2, 3, 5, 7, 11 };
	REQUIRE(GeneratePrimeNumbersSet(11) == set);
}

#if !defined(_DEBUG)
	SCENARIO("UPPER = 100000000, COUNT OF PRIMES IS 5761455, LESS THAN 12 SEC")
	{
		auto start = clock();
		Set set = GeneratePrimeNumbersSet(100000000);
		auto end = clock();
		REQUIRE(set.size() == 5761455);
		REQUIRE(end - start < 12000);
	}
#endif

