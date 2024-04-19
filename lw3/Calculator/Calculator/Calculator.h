#pragma once
#include "DataElement.h"
#include "Function.h"
#include "Variable.h"
#include "OperationList.h"
#include <memory>
#include <unordered_map>
#include <string>

class CCalculator
{
public:
	void CreateVariable(const std::string & name);
	void SetValueToVariable(const std::string& variableName, const std::string& valueElementName);
	void SetValueToVariable(const std::string & variableName, double value);
	void PrintVariables();

	void CreateFunction(const std::string & name, const std::string & dependency1Name);
	void CreateFunction(const std::string & name, const std::string & dependency1Name, const std::string & dependency2Name, char operation);
	void PrintFunctions();
	void PrintElement(const std::string & elementName);

private:
	void UpdateValues(std::shared_ptr<CDataElement> element);
	std::shared_ptr<CDataElement> GetPointer(const std::string & name);
	std::unordered_map<std::string, std::shared_ptr<CVariable>> m_variables;
	std::unordered_map<std::string, std::shared_ptr<CFunction>> m_functions;
};
