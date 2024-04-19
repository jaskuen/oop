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

double CDataElement::Value()
{
    if (!m_value.has_value())
    {
        return NAN;
    }
    return m_value.value();
}

const std::string & CDataElement::Name()
{
    return m_name;
}

void CDataElement::Print()
{
    if (!m_value.has_value())
    {
        std::cout << "not initialized" << std::endl;
    }
    else
    {
        std::cout << std::fixed << std::setprecision(2) << m_value.value() + .0 << std::endl;
    }
}
