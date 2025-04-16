#include "CMyString.h"
#include <locale>
#include <memory>

char* Allocate(size_t size)
{
	return new char[size]();
}

void ReleaseMemory(const char* chars)
{
	delete[] chars;
}

CMyString::CMyString()
	: m_capacity(1),
	  m_size(0),
	  m_chars(Allocate(1))
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_capacity(length + 1),
	m_size(length),
	m_chars(Allocate(length + 1))
{
	auto end = std::uninitialized_copy_n(pString, m_size, m_chars);
	*end = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_chars, other.m_size)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_size(other.m_size),
	m_capacity(other.m_capacity),
	m_chars(other.m_chars)
{
	other.m_size = 0;
	other.m_capacity = 1;
	other.m_chars = Allocate(1);
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	ReleaseMemory(m_chars);
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_size)
	{
		throw std::out_of_range("Start position out of range");
	}

	size_t finalLength = std::min(length, m_size - start);

	return CMyString(m_chars + start, finalLength);
}

void CMyString::Clear()
{
	ReleaseMemory(m_chars);
	m_capacity = 1;
	m_chars = Allocate(1);
	m_size = 0;
}

size_t CMyString::GetCapacity()
{
	return m_capacity;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		if (m_capacity >= other.m_size && m_chars != s_emptyString)
		{
			std::destroy_n(m_chars, m_size + 1);
			std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
			m_size = other.m_size;
		}
		else
		{
			CMyString copy{ other };
			std::swap(m_size, copy.m_size);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_chars, copy.m_chars);
		}
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_chars, other.m_chars);
	}
	return *this;
}

CMyString CMyString::operator+(const CMyString& other) const
{
	CMyString str;

	str.m_size = m_size + other.m_size;
	str.m_capacity = str.m_size + 1;

	str.m_chars = Allocate(str.m_capacity);
	std::memcpy(str.m_chars, m_chars, m_size);
	std::memcpy(str.m_chars + m_size, other.m_chars, other.m_size);
	str.m_chars[str.m_size] = '\0';

	return str;
}

CMyString CMyString::operator+(const std::string& other) const
{
	return *this + CMyString(other);
}

CMyString CMyString::operator+(const char* other) const
{
	return *this + CMyString(other);
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	if (other.m_size + m_size >= m_capacity)
	{
		m_capacity = std::max(other.m_size + m_size + 1, m_capacity * 2);
		
		auto chars = Allocate(m_capacity);
		std::memcpy(chars, m_chars, m_size);
		m_chars = chars;
	}

	std::memcpy(m_chars + m_size, other.m_chars, other.m_size + 1);
	m_size = m_size + other.m_size;

	return *this;
}

bool CMyString::operator==(const CMyString& other) const
{
	return strcmp(m_chars, other.m_chars) == 0;
}

bool CMyString::operator!=(const CMyString& other) const
{
	return !(*this == other);
}

bool CMyString::operator<(const CMyString& other) const
{
	return strcmp(m_chars, other.m_chars) < 0;
}

bool CMyString::operator>(const CMyString& other) const
{
	return strcmp(m_chars, other.m_chars) > 0;
}

bool CMyString::operator<=(const CMyString& other) const
{
	return !(*this > other);
}

bool CMyString::operator>=(const CMyString& other) const
{
	return !(*this < other);
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_chars[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_chars[index];
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
	return os << str.m_chars;
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
	std::string word;
	is >> word;
	str = CMyString(word);
	return is;
}
