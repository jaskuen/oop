#include "WorkWithVector.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <functional>

double SumPositive(double result, double number)
{
	if (number < 0)
	{
		return result;
	}
	return result + number;
}

bool IsPositive(double num) { return num > 0; }

size_t CountPositiveElements(const std::vector<double>& array)
{
	// count_if (cppreference)
	return std::ranges::count_if(array, IsPositive);
}

double AverageOfPositive(const std::vector<double>& array)
{
	size_t countOfPositive = CountPositiveElements(array);
	if (countOfPositive == 0)
	{
		return 0;
	}
	return std::accumulate(array.begin(), array.end(), 0.0, SumPositive) / (countOfPositive + .0);
}

void AddAverageOfPositiveToEachElement(std::vector<double>& array)
{
	double averageOfPositive = AverageOfPositive(array);
	std::transform(array.cbegin(), array.cend(), array.begin(),
		[averageOfPositive](double item) { return item + averageOfPositive; });
	//std::transform 
}

void ReadVectorFromIstream(std::vector<double>& array, std::istream& inputStream)
{
	double num;
	while (inputStream >> num)
	{
		array.push_back(num);
	}
}

void WriteVectorIntoOstream(const std::vector<double>& array, std::ostream& outputStream)
{
	for (double num : array)
	{
		outputStream << std::setprecision(5) << num << " ";
	}
	outputStream << std::endl;
}
