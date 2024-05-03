#include "Calculator.h"
#include "Variable.h"
#include "Function.h"
#include "UpdateQueue.h"
#include <iostream>
#include <unordered_set>
#include <queue>

CCalculator::~CCalculator()
{
}

void CCalculator::CreateVariable(const std::string & name)
{
	if (m_variables.find(name) != m_variables.end() || m_functions.find(name) != m_functions.end())
	{
		return;
	} 
	std::shared_ptr<CVariable> variable = std::make_shared<CVariable>(name);
	m_variables[name] = variable; // проверка на наличие этого имени в списке и exception
}

void CCalculator::SetValueToVariable(const std::string& variableName, const std::string& valueElementName)
{
	CreateVariable(variableName);
	double valueElementValue = GetDataElement(valueElementName)->Value();
	auto variableIter = m_variables.find(variableName)->second;
	variableIter->Set(valueElementValue);
	UpdateValues(variableIter);
}

void CCalculator::SetValueToVariable(const std::string & variableName, double value)
{
	CreateVariable(variableName);
	auto variableIter = m_variables.find(variableName)->second;
	variableIter->Set(value);
	UpdateValues(variableIter);
}

void CCalculator::CreateFunction(const std::string & name, const std::string & operand) // operand/operator
{
	if (m_variables.find(name) != m_variables.end() || m_functions.find(name) != m_functions.end())
	{
		return;
	} 
	std::shared_ptr<CDataElement> operandPtr = GetDataElement(operand);
	std::shared_ptr<CFunction> newOperator = std::make_shared<CFunction>(name, operandPtr);
	m_functions[name] = newOperator;
	operandPtr->AddDependent(newOperator);
}

void CCalculator::CreateFunction(const std::string & name, const std::string & operand1, const std::string & operand2, char operation)
{
	if (m_variables.find(name) != m_variables.end() || m_functions.find(name) != m_functions.end())
	{
		return;
	} 
	std::shared_ptr<CDataElement> operand1Ptr = GetDataElement(operand1);
	std::shared_ptr<CDataElement> operand2Ptr = GetDataElement(operand2);
	std::shared_ptr<CFunction> newOperator = std::make_shared<CFunction>(name, operand1Ptr, operand2Ptr, operation);
	m_functions[name] = newOperator;
	operand1Ptr->AddDependent(newOperator);
	operand2Ptr->AddDependent(newOperator);
}

void CCalculator::Variables(std::function<void(std::vector<std::pair<std::string, std::shared_ptr<CVariable>>>)> printCallback) const
{
	std::vector<std::pair<std::string, std::shared_ptr<CVariable>>> variables(m_variables.begin(), m_variables.end());
	std::sort(variables.begin(), variables.end(),
		[](const std::pair<std::string, std::shared_ptr<CVariable>>& a, const std::pair<std::string, std::shared_ptr<CVariable>>& b) {
			return a.first < b.first;
		});
	printCallback(variables);
}

void CCalculator::Functions(std::function<void(std::vector<std::pair<std::string, std::shared_ptr<CFunction>>>)> printCallback) const
{
	std::vector<std::pair<std::string, std::shared_ptr<CFunction>>> functions(m_functions.begin(), m_functions.end());
	std::sort(functions.begin(), functions.end(),
		[](const std::pair<std::string, std::shared_ptr<CFunction>>& a, const std::pair<std::string, std::shared_ptr<CFunction>>& b) {
			return a.first < b.first;
		});
	printCallback(functions);
}

double CCalculator::GetValue(const std::string& name) const
{
	auto pointer = GetDataElement(name);
	return pointer.get()->Value();
}

std::vector<std::weak_ptr<CFunction>> CCalculator::GetDependents(std::weak_ptr<CDataElement> element)
{
	std::vector<std::weak_ptr<CFunction>> dependentFunctions;
	for (const auto& pair : m_functions)
	{
		if (pair.second->DependsOn(element))
		{
			dependentFunctions.push_back(pair.second);
		}
	}
	return dependentFunctions;
}

void CCalculator::UpdateValues(std::shared_ptr<CDataElement> element)
{
	std::queue<std::weak_ptr<CFunction>> functionQueue;
	std::vector<std::weak_ptr<CFunction>> dependentFunctions = element->GetDependents();
	std::unordered_set<std::shared_ptr<CFunction>> processedFunctions;

	// Функция для добавления функции в очередь, если она еще не была обработана
	auto addToQueueIfNotProcessed = [&](const std::weak_ptr<CFunction>& func) {
		if (processedFunctions.find(func.lock()) == processedFunctions.end()) {
			functionQueue.push(func);
			processedFunctions.insert(func.lock());
		}
		};

	// Добавляем все функции без зависимостей в очередь
	for (auto const& func : dependentFunctions) {
		if (func.lock()->DependencyAnotherFrom(element).expired()) {
			addToQueueIfNotProcessed(func.lock());
		}
	}

	while (!functionQueue.empty()) {
		// Берем функцию из очереди
		std::weak_ptr<CFunction> currentFunction = functionQueue.front();
		functionQueue.pop();

		// Обновляем значение функции
		currentFunction.lock()->Update();

		// Получаем зависимости этой функции
		std::vector<std::weak_ptr<CFunction>> dependencies = currentFunction.lock()->GetDependents();

		// Добавляем все зависимые функции в очередь для дальнейшей обработки
		for (const auto& dependency : dependencies) {
			addToQueueIfNotProcessed(dependency);
		}
	}
}

std::shared_ptr<CDataElement> CCalculator::GetDataElement(const std::string & name) const
{
	if (m_variables.find(name) != m_variables.end())
	{
		return m_variables.at(name);
	}
	else if (m_functions.find(name) != m_functions.end())
	{
		return m_functions.at(name);
	}
	throw std::invalid_argument("No element with '" + name + "' name found");
}
