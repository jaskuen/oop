#pragma once

#include <memory>
#include "DataElement.h"

struct Element
{
	std::shared_ptr<CDataElement> pointer;
	std::shared_ptr<Element> next;
};

class UpdateQueue
{
public:
	UpdateQueue()
	{
		ClearQueue();
		m_end = m_start;
	}
	void Push(std::shared_ptr<CDataElement> ptr)
	{
		std::shared_ptr<Element> newPtr;
		newPtr->pointer = ptr;
		newPtr->next = m_end;
		m_end = newPtr;
	}

	std::shared_ptr<CDataElement> Pop()
	{
		std::shared_ptr<CDataElement> value = m_start->pointer;
		m_start = m_start->next;
		return value;
	}

	void ClearQueue()
	{
		std::shared_ptr<Element> newStart = std::make_shared<Element>();
		m_start = newStart;
	}
private:
	std::shared_ptr<Element> m_start;
	std::shared_ptr<Element> m_end;
};