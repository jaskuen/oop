#pragma once
#include <vector>

template < typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{

	if (arr.size() == 0)
	{
		return false;
	}

	maxValue = arr[0];
	for (const T& elem : arr)
	{
		// less может кинуть исключение, обработать + commit-rollback
		if (less(maxValue, elem))
		{
			maxValue = elem;
		}
	}
	return true;
};