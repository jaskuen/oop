// CMyArray.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <array>
#include "CMyArray.h"

int main()
{
	CMyArray<int> arr;
	arr.Resize(10);
	std::cout << arr.Size();
}
