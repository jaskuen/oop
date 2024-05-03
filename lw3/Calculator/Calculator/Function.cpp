#include "Function.h"
#include "OperationList.h"
#include <iostream>


CFunction::~CFunction()
{
}
// утечка памяти
CFunction::CFunction(const CFunction&)
{
}

CFunction::CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr)
{
    m_name = name;
    m_dependency1Ptr = dependency1Ptr;

    m_value = m_dependency1Ptr.lock()->Value();
}

CFunction::CFunction(const std::string & name, std::shared_ptr<CDataElement> dependency1Ptr, std::shared_ptr<CDataElement> dependency2Ptr, char relation)
{
    m_name = name;
    m_dependency1Ptr = dependency1Ptr;
    m_dependency2Ptr.emplace(std::move(dependency2Ptr));
    m_relation.emplace(relation);

    m_value.emplace(CalculateFunctionValue());
}

bool CFunction::DependsOn(std::weak_ptr<CDataElement> elementPtr)
{
    if (!m_dependency2Ptr)
    {
        return (m_dependency1Ptr.lock() == elementPtr.lock());
    }
    return (m_dependency1Ptr.lock() == elementPtr.lock()
        || m_dependency2Ptr.value().lock() == elementPtr.lock());
}

std::weak_ptr<CDataElement> CFunction::DependencyAnotherFrom(std::shared_ptr<CDataElement> element)
{
    if (m_dependency1Ptr.lock() == element)
    {
        if (m_dependency2Ptr.has_value())
        {
            if (m_dependency2Ptr.value().lock() == element)
            {
                return m_dependency2Ptr.value();
            }
            return std::weak_ptr<CDataElement>();
        }
        return std::weak_ptr<CDataElement>();
    }
    return m_dependency1Ptr;
}



double CFunction::CalculateFunctionValue() const
{
    if (m_dependency2Ptr.has_value())
    {
        auto it = OperationList::OperationMap.find(m_relation.value());
        return it->second(m_dependency1Ptr.lock(), m_dependency2Ptr.value().lock());
    }
    // делать проверки на null
    // хранить хотя бы одну сильную ссылку в одну сторону
    return m_dependency1Ptr.lock()->Value();
}

void CFunction::Update()
{
    m_value.emplace(CalculateFunctionValue());
}

void CFunction::AddDependent(std::weak_ptr<CFunction> dependent)
{
    m_dependents.push_back(dependent);
}

std::vector<std::weak_ptr<CFunction>> CFunction::GetDependents()
{
    return m_dependents;
}
