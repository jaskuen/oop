#include "Function.h"
#include "OperationList.h"
#include <iostream>


CFunction::~CFunction()
{
}

CFunction::CFunction(const CFunction&)
{
}

CFunction::CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr)
{
    m_name = name;
    m_dependency1Ptr = dependency1Ptr;

    m_value = m_dependency1Ptr->Value();
}

CFunction::CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr, std::shared_ptr<CDataElement> dependency2Ptr, char relation)
{
    m_name = name;
    m_dependency1Ptr = dependency1Ptr;
    m_dependency2Ptr.emplace(std::move(dependency2Ptr));
    m_relation.emplace(relation);

    m_value.emplace(CalculateFunctionValue(m_dependency1Ptr, m_dependency2Ptr));
}

bool CFunction::DependsOn(std::shared_ptr<CDataElement> elementPtr)
{
    if (!m_dependency2Ptr)
    {
        return (m_dependency1Ptr->Name() == elementPtr->Name());
    }
    return (m_dependency1Ptr->Name() == elementPtr->Name()
        || m_dependency2Ptr.value()->Name() == elementPtr->Name());
}

double CFunction::CalculateFunctionValue(std::shared_ptr<CDataElement> ptr1, std::optional<std::shared_ptr<CDataElement>> ptr2)
{
    if (ptr2.has_value())
    {
        auto it = OperationList::OperationMap.find(m_relation.value());
        return it->second(m_dependency1Ptr, m_dependency2Ptr.value());
    }
    return ptr1->Value();
}

void CFunction::Update()
{
    m_value.emplace(CalculateFunctionValue(m_dependency1Ptr, m_dependency2Ptr));
}
