#include "UserInterface.h"
#include "CommandError.h"
#include "Car.h"
#include <iostream>
#include <sstream>
#include <string>
#include <array> 
#include <algorithm>

CommandError errList;

void CUserInterface::WriteCommandList()
{
	std::cout << "Введите одну из предложенных команд:" <<
		"\nInfo - узнать текущее состояние машины" <<
		"\nEngineOn - включить двигатель" <<
		"\nEngineOff - выключить двигатель" <<
		"\nSetGear  <номер передачи -1..5> - сменить передачу" <<
		"\nSetSpeed <скорость> - установить скорость автомобиля на текущую(задается положительным числом)" <<
		"\nExit - выйти из программы" << std::endl;
}

CUserInterface::CUserInterface(CCar& car, bool& exit, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_exit(exit)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "info", bind_front(&CUserInterface::Info, this) },
		{ "engineon", bind(&CUserInterface::TurnOnEngine, this, std::placeholders::_1) },
		{ "engineoff", bind(&CUserInterface::TurnOffEngine, this, std::placeholders::_1) },
		{ "setgear", bind(&CUserInterface::SetGear, this, std::placeholders::_1) },
		{ "setspeed", bind(&CUserInterface::SetSpeed, this, std::placeholders::_1) },
		{ "exit", bind (&CUserInterface::Exit, this, std::placeholders::_1)},
	})
{
}

std::string StringToLowerCase(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return std::tolower(c); }
	);
	return s;
}

bool CUserInterface::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(StringToLowerCase(action));
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CUserInterface::Info(std::istream& args)
{
	m_car.Info();
	return true;
}

bool CUserInterface::TurnOnEngine(std::istream& args)
{
	if (m_car.TurnOnEngine())
	{
		return true;
	}
	return false;
}

bool CUserInterface::TurnOffEngine(std::istream& args)
{
	if (m_car.TurnOffEngine())
	{
		return true;
	}
	return false;
}

bool CUserInterface::SetGear(std::istream& args)
{
	int gearNumber;
	args >> gearNumber;
	if (m_car.SetGear(gearNumber))
	{
		return true;
	}
	return false;
}

bool CUserInterface::SetSpeed(std::istream& args)
{
	int speedNumber;
	args >> speedNumber;
	if (m_car.SetSpeed(speedNumber))
	{
		return true;
	}
	return false;
}

bool CUserInterface::Exit(std::istream& args)
{
	return m_exit = true;
}
	