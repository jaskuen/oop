#pragma once

#include "DataElement.h"

class CVariable : public CDataElement
{
public:
	~CVariable();
	CVariable(const std::string & name);
	CVariable(const std::string & name, double value);
	CVariable(const std::string & name, std::shared_ptr<CDataElement> elementPtr);
	void AddDependent(std::shared_ptr<CFunction> dependent);
	std::vector<std::shared_ptr<CFunction>> GetDependents();
private:
	std::vector<std::shared_ptr<CFunction>> m_dependents;
};
