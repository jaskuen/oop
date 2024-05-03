#pragma once
#include <string>
#include <optional>
#include <memory>
#include <vector>

class CFunction;
class CDataElement
{
public:
	virtual ~CDataElement() = default;
	CDataElement() = default;
	CDataElement(const std::string & name);
	void Set(double newValue);
	double Value() const; // пересмотреть все классы на наличие константных методов
	const std::string & Name() const; 
	virtual void AddDependent(std::weak_ptr<CFunction> dependent);
	virtual std::vector<std::weak_ptr<CFunction>> GetDependents() const;
protected:
	std::vector<std::weak_ptr<CFunction>> m_dependents;
	std::string m_name;
	std::optional<double> m_value;
};
