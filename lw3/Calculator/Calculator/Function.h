#pragma once

#include "DataElement.h"
#include "OperationList.h"
#include <optional>
#include <functional>
#include <memory>

class CFunction : public CDataElement
{
public:
	~CFunction();
	CFunction(const CFunction&);
	CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr);
	CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr, std::shared_ptr<CDataElement> dependency2Ptr, char relation);
	bool DependsOn(std::shared_ptr<CDataElement> elementPtr);
	double CalculateFunctionValue(std::shared_ptr<CDataElement> ptr1, std::optional<std::shared_ptr<CDataElement>> ptr2);
	void Update();
private:
	std::shared_ptr<CDataElement> m_dependency1Ptr;
	std::optional<char> m_relation;
	std::optional<std::shared_ptr<CDataElement>> m_dependency2Ptr;
};
