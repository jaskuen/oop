#include "Calculator.h"
#include "Variable.h"
#include "Function.h"
#include <iostream>

void CCalculator::CreateVariable(const std::string & name)
{
	std::shared_ptr<CVariable> variable = std::make_shared<CVariable>(name);
	m_variables[name] = variable;
}

void CCalculator::SetValueToVariable(const std::string& variableName, const std::string& valueElementName)
{
	if (m_variables.find(variableName) == m_variables.end())
	{
		CreateVariable(variableName);
	}
	std::shared_ptr<CDataElement> element = GetPointer(valueElementName);
	m_variables[variableName]->Set(element->Value());
	UpdateValues(m_variables[variableName]);
}

void CCalculator::SetValueToVariable(const std::string & variableName, double value)
{
	if (m_variables.find(variableName) == m_variables.end())
	{
		CreateVariable(variableName);
	}
	m_variables[variableName]->Set(value);
	UpdateValues(m_variables[variableName]);
}

void CCalculator::CreateFunction(const std::string & name, const std::string & dependency1Name)
{
	CFunction newF = CFunction(name, GetPointer(dependency1Name));
	std::shared_ptr<CFunction> func = std::make_shared<CFunction>(name, GetPointer(dependency1Name));
	m_functions[name] = func;
}

void CCalculator::CreateFunction(const std::string & name, const std::string & dependency1Name, const std::string & dependency2Name, char operation)
{
	std::shared_ptr<CFunction> func = std::make_shared<CFunction>(name, GetPointer(dependency1Name), GetPointer(dependency2Name), operation);
	m_functions[name] = func;
}

void CCalculator::PrintFunctions()
{
	for (const auto& pair : m_functions)
	{
		std::cout << pair.first << ":" << pair.second->Value() << std::endl;
	}
}

void CCalculator::PrintVariables()
{
	for (const auto& pair : m_variables)
	{
		std::cout << pair.first << ":" << pair.second->Value() << std::endl;
	}
}

void CCalculator::PrintElement(const std::string & elementName)
{
	ptr pointer = GetPointer(elementName);
	std::cout << elementName << " " << pointer->Value() << std::endl;
}

void CCalculator::UpdateValues(std::shared_ptr<CDataElement> element)
{
	for (const auto& pair : m_functions)
	{
		if (pair.second->DependsOn(element))
		{
			pair.second->Update();
		}
	}
}

std::shared_ptr<CDataElement> CCalculator::GetPointer(const std::string & name)
{
	std::shared_ptr<CDataElement> pointer = nullptr;
	if (m_variables.find(name) != m_variables.end())
	{
		pointer = m_variables.at(name);
	}
	else if (m_functions.find(name) != m_functions.end())
	{
		pointer = m_functions.at(name);
	}
	else
	{
		throw std::invalid_argument("No element with '" + name + "' name found");
	}
	return pointer;
}
