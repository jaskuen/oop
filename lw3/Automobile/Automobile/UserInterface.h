#pragma once

#include "Car.h"
#include <functional>

class CUserInterface // привязать ссылку на автомобиль 
{
public:
	CUserInterface(CCar& car, bool & exit, std::istream& input, std::ostream& output);
	void WriteCommandList();
	bool HandleCommand();
private:
	bool Info(std::istream& args);
	bool TurnOnEngine(std::istream& args);
	bool TurnOffEngine(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);
	bool Exit(std::istream& args);
private:
	using Handler = std::function<bool(std::istream& input)>;

	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	bool& m_exit;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
