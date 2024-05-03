#pragma once

#include "DataElement.h"
#include "OperationList.h"

class CFunction : public CDataElement
{
public:
	~CFunction();
	CFunction(const CFunction&);
	CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr);
	CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr, std::shared_ptr<CDataElement> dependency2Ptr, char relation);
	bool DependsOn(std::weak_ptr<CDataElement> elementPtr);
	std::weak_ptr<CDataElement> DependencyAnotherFrom(std::shared_ptr<CDataElement> element);
	double CalculateFunctionValue() const;
	void Update();
	void AddDependent(std::weak_ptr<CFunction> dependent);
	std::vector<std::weak_ptr<CFunction>> GetDependents();
private:
	std::vector<std::weak_ptr<CFunction>> m_dependents;
	std::weak_ptr<CDataElement> m_dependency1Ptr;
	std::optional<char> m_relation;
	std::optional<std::weak_ptr<CDataElement>> m_dependency2Ptr;
};
