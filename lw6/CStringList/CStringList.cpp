#include "CStringList.h"

void CStringList::Allocate(size_t size)
{
	std::string* newData = new std::string[size]();
	if (m_start == nullptr)
	{
		m_start = newData;
		return;
	}

	std::copy(m_start, m_start + m_size, newData);
	m_start = newData;
}

CStringList::CStringList()
	: m_size(0),
	m_start(nullptr)
{
}

CStringList::CStringList(const CStringList& other)
	: m_size(other.m_size)
{
	Allocate(m_size);
	std::copy(other.m_start, other.m_start + other.m_size, m_start);
}

CStringList::CStringList(CStringList&& other) noexcept
	: m_size(std::exchange(other.m_size, 0)),
	m_start(std::exchange(other.m_start, nullptr))
{
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (this != &other)
	{
		CStringList copy{ other };
		std::swap(m_size, copy.m_size);
		std::swap(m_start, copy.m_start);
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_start, other.m_start);
	}
	return *this;
}

CStringList::~CStringList() noexcept
{
	Clear();
}

void CStringList::PushBack(const std::string& str)
{
	Allocate(m_size + 1);
	m_start[m_size++] = str;
}

void CStringList::PushFront(const std::string& str)
{
	Allocate(m_size + 1);

	std::string* newStart = new std::string[m_size + 1]();
	newStart[0] = str;
	std::copy(m_start, m_start + m_size, newStart + 1);

	m_start = newStart;
	m_size++;
}

void CStringList::Clear()
{
	if (m_start != nullptr)
	{
		delete[] m_start;
	}
	m_start = nullptr;
	m_size = 0;
}

size_t CStringList::Size()
{
	return m_size;
}

std::string* CStringList::begin()
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("List is empty");
	}
	return m_start;
}

const std::string* CStringList::cbegin() const
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("List is empty");
	}
	return m_start;
}

std::string* CStringList::end()
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("List is empty");
	}
	return m_start + m_size;
}

const std::string* CStringList::cend() const
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("List is empty");
	}
	return m_start + m_size;
}

std::reverse_iterator<std::string*> CStringList::rbegin()
{
	return std::reverse_iterator<std::string*>(end());
}

std::reverse_iterator<const std::string*> CStringList::crbegin() const
{
	return std::reverse_iterator<const std::string*>(cend());
}

std::reverse_iterator<std::string*> CStringList::rend()
{
	return std::reverse_iterator<std::string*>(begin());
}

std::reverse_iterator<const std::string*> CStringList::crend() const
{
	return std::reverse_iterator<const std::string*>(cbegin());
}
