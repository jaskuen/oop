#include "UserInterface.h"
#include <sstream>
#include <algorithm>

//убрать лишние include

CUserInterface::CUserInterface(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "var", bind_front(&CUserInterface::CreateVariable, this) },
		{ "let", bind_front(&CUserInterface::SetValueToVariable, this) },
		{ "fn", bind_front(&CUserInterface::CreateFunction, this) },
		{ "print", bind_front(&CUserInterface::PrintElement, this)},
		{ "printvars", bind_front(&CUserInterface::PrintVariables, this) },
		{ "printfns", bind_front(&CUserInterface::PrintFunctions, this) },
		})
{
}

std::string StringToLowerCase(std::string& s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return std::tolower(c); }
	);
	return s;
}

bool CUserInterface::HandleCommand(const std::string & line)
{
	std::istringstream strm(line);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(StringToLowerCase(action));
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CUserInterface::CreateVariable(std::istream& args)
{
	std::string name;
	args >> name;
	m_calculator.CreateVariable(name);
	return true;
}

bool CUserInterface::SetValueToVariable(std::istream& args)
{
	std::string name;
	std::getline(args >> std::ws, name, '=');
	std::string valueStr;
	double value;
	args >> valueStr;
	if (valueStr.find_first_of("0123456789") == std::string::npos)
	{
		m_calculator.SetValueToVariable(name, valueStr);
	}
	else
	{
		value = std::stod(valueStr);
		m_calculator.SetValueToVariable(name, value);
	}
	return false;
}

bool CUserInterface::CreateFunction(std::istream& args)
{
	std::string name;
	std::getline(args >> std::ws, name, '=');
	std::string rest;
	args >> rest;
	auto indexOfSign = rest.find_first_of("+-*/");
	if (indexOfSign == std::string::npos)
	{
		m_calculator.CreateFunction(name, rest);
	}
	else
	{
		const std::string & arg1 = rest.substr(0, indexOfSign);
		const std::string & arg2 = rest.substr(indexOfSign + 1);
		char operation = rest.at(indexOfSign);
		m_calculator.CreateFunction(name, arg1, arg2, operation);
	}
	return false;
}

bool CUserInterface::PrintElement(std::istream& args)
{
	std::string name;
	args >> name;
	double value = m_calculator.GetValue(name);
	std::cout << name << ":" << value << std::endl;
	return false;
}

void PrintFuntionsCallback(std::vector<std::pair<std::string, std::shared_ptr<CFunction>>> functionList)
{
	for (const auto& pair : functionList)
	{
		std::cout << pair.first << ":" << pair.second->Value() << std::endl;
	}
}

void PrintVariablesCallback(std::vector<std::pair<std::string, std::shared_ptr<CVariable>>> variableList)
{
	for (const auto& pair : variableList)
	{
		std::cout << pair.first << ":" << pair.second->Value() << std::endl;
	}
}

bool CUserInterface::PrintFunctions(std::istream& args)
{
	m_calculator.Functions(PrintFuntionsCallback);
	return false;
}

bool CUserInterface::PrintVariables(std::istream& args)
{
	m_calculator.Variables(PrintVariablesCallback);
	return false;
}
