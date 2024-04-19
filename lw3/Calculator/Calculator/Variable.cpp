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


