#pragma once
#include <string>
#include <optional>
#include <memory>

class CDataElement
{
public:
	CDataElement() = default;
	CDataElement(const std::string & name);
	void Set(double newValue);
	double Value();
	const std::string & Name();
	void Print();
protected:
	std::string m_name;
	std::optional<double> m_value;
};
