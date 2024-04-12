#include "UserInterface.h"
#include "Car.h"
#include <iostream>

// при движении назад нельзя менять передачу на переднюю
int main(int argc, char* argv[]) // при переключнении на неправильную передачу нет сообщения об ошибке
{
	system("chcp 1251");
	system("cls");
	CCar car = CCar();
	bool exitProgram = false;
	CUserInterface UI(car, exitProgram, std::cin, std::cout);
	try
	{
		while (!exitProgram)
		{
			system("cls");
			UI.WriteCommandList();
			UI.HandleCommand();
			if (!exitProgram)
			{
				std::cin.ignore(); // пауза
			}
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}