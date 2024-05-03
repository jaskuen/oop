#include "DataElement.h"
#include <iostream>
#include <iomanip>


CDataElement::CDataElement(const std::string & name)
    : m_name(name), m_value(std::nullopt)
{
}

void CDataElement::Set(double newValue)
{
    m_value = newValue;
}

double CDataElement::Value() const
{
    return m_value.value_or(NAN);
}

void CDataElement::AddDependent(std::weak_ptr<CFunction> dependent)
{
    m_dependents.push_back(dependent);
}

std::vector<std::weak_ptr<CFunction>> CDataElement::GetDependents() const
{
    return m_dependents;
}

