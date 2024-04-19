#pragma once

#include <string>
#include "DataElement.h"

class CVariable : public CDataElement
{
public:
	~CVariable();
	CVariable(const std::string & name);
	CVariable(const std::string & name, double value);
	CVariable(const std::string & name, std::shared_ptr<CDataElement> elementPtr);
};
