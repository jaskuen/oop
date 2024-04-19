#include "Calculator.h"
#include "UserInterface.h"
#include <iostream>

int main(int argc, char* argv[])
{
	CCalculator calculator;
	CUserInterface UI = CUserInterface(calculator, std::cin, std::cout);
	std::string line;
	while (std::getline(std::cin, line))
	{
		try 
		{
			UI.HandleCommand(line);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return EXIT_SUCCESS;
}