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
	~CCalculator();
	void CreateVariable(const std::string & name);
	void SetValueToVariable(const std::string& variableName, const std::string& valueElementName);
	void SetValueToVariable(const std::string & variableName, double value);

	void CreateFunction(const std::string & name, const std::string & operand);
	void CreateFunction(const std::string & name, const std::string & dependency1Name, const std::string & dependency2Name, char operation);
	void Variables(std::function<void(std::vector<std::pair<std::string, std::shared_ptr<CVariable>>>)> printCallback) const; // метод принимает callback, позволит не выставлять наружу приватные данные класса
	void Functions(std::function<void(std::vector<std::pair<std::string, std::shared_ptr<CFunction>>>)> printCallback) const;
	double GetValue(const std::string& name) const;
private:
	std::shared_ptr<CDataElement> GetDataElement(const std::string& name) const;
	std::vector<std::weak_ptr<CFunction>> GetDependents(std::weak_ptr<CDataElement> element);
	void UpdateValues(std::shared_ptr<CDataElement> element);
	std::unordered_map<std::string, std::shared_ptr<CVariable>> m_variables;
	std::unordered_map<std::string, std::shared_ptr<CFunction>> m_functions;
};
