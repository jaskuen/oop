#include "Calculator.h"
#include "UserInterface.h"
#include <ctime>

int main(int argc, char* argv[])
{
	unsigned int start_time = clock();
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
	unsigned int end_time = clock();
	std::cout << "Time: " << end_time - start_time << std::endl;
	return EXIT_SUCCESS;
}