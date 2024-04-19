#pragma once

#include <functional>
#include <iostream>
#include <map>
#include "Calculator.h"

class CUserInterface
{
public:
	CUserInterface(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand(const std::string & line);
private:
	bool CreateVariable(std::istream& args);
	bool SetValueToVariable(std::istream& args);
	bool CreateFunction(std::istream& args);
	bool PrintElement(std::istream& args);
	bool PrintFunctions(std::istream& args);
	bool PrintVariables(std::istream& args);

private:
	using Handler = std::function<bool(std::istream& input)>;

	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
