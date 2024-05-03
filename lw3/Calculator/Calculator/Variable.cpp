#include "Variable.h"


CVariable::~CVariable()
{
}

CVariable::CVariable(const std::string & name)
{
	m_name = name;
}

CVariable::CVariable(const std::string & name, double value)
{
	m_name = name;
	m_value = value;
}

CVariable::CVariable(const std::string & name, std::shared_ptr<CDataElement> elementPtr)
{
	m_name = name;
	m_value = elementPtr->Value();
}

void CVariable::AddDependent(std::shared_ptr<CFunction> dependent)
{
	m_dependents.push_back(dependent);
}

std::vector<std::shared_ptr<CFunction>> CVariable::GetDependents()
{
	return m_dependents;
}


