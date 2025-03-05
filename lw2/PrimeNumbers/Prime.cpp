#include "Prime.h"
#include <vector>
#include <math.h>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primes;
	if (upperBound < 0)
	{
		return primes;
	}
	std::vector<bool> isPrime(upperBound + 1, true);
	for (int i = 2; i <= floor(sqrt(upperBound)); i++)
	{
		if (!isPrime[i])
		{
			continue;
		}
		int multiplier = 2;
		while (multiplier * i <= upperBound)
		{
			isPrime[multiplier * i] = false;
			multiplier++;
		}
	}
	for (int i = 2; i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			primes.insert(i);
		}
	}
	return primes;
}
