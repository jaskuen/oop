#pragma once
#include <iterator>

template <typename T>
class CMyArray
{
public:
	CMyArray();
	CMyArray(const CMyArray& other);
	CMyArray(CMyArray&& other);

	~CMyArray() noexcept;

	void Push(const T& elem);
	size_t Size();
	size_t Capacity();
	void Resize(size_t size);
	void Clear();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	CMyArray& operator=(const CMyArray& other);
	CMyArray& operator=(CMyArray&& other);

	T* begin();
	const T* cbegin() const;
	T* end();
	const T* cend() const;

	std::reverse_iterator<T*> rbegin();
	std::reverse_iterator<const T*> crbegin() const;
	std::reverse_iterator<T*> rend();
	std::reverse_iterator<const T*> crend() const;

private:
	void Allocate(size_t size);

	T* m_start;

	size_t m_size;
	size_t m_capacity;
};

// Реализация класса

template<typename T>
void CMyArray<T>::Allocate(size_t size)
{
	m_capacity = size;
	T* newData = new T[size]();
	if (m_start == nullptr)
	{
		m_start = newData;
		return;
	}

	std::copy(m_start, m_start + m_size, newData);
	m_start = newData;
}

template<typename T>
CMyArray<T>::CMyArray()
	: m_start(nullptr),
	m_size(0),
	m_capacity(0)
{
}

template<typename T>
CMyArray<T>::CMyArray(const CMyArray& other)
	: m_size(other.m_size),
	m_capacity(other.m_capacity)
{
	T* temp = nullptr;
	if (other.m_start != nullptr)
	{
		temp = new T[m_size];
		std::copy(other.m_start, other.m_start + m_size, temp);
	}
	m_start = temp;
}

template<typename T>
CMyArray<T>::CMyArray(CMyArray&& other)
	: m_size(std::exchange(other.m_size, 0)),
	m_capacity(std::exchange(other.m_capacity, 0)),
	m_start(std::exchange(other.m_start, nullptr))
{
}


template<typename T>
CMyArray<T>::~CMyArray() noexcept
{
	Clear();
}

template<typename T>
void CMyArray<T>::Push(const T& elem)
{
	if (m_capacity == m_size)
	{
		Allocate(m_size == 0 ? 1 : m_size * 2);
	}

	m_start[m_size++] = elem;
}

template<typename T>
size_t CMyArray<T>::Size()
{
	return m_size;
}

template<typename T>
inline size_t CMyArray<T>::Capacity()
{
	return m_capacity;
}

template<typename T>
void CMyArray<T>::Resize(size_t size)
{
	Allocate(size);
}

template<typename T>
void CMyArray<T>::Clear()
{	
	if (m_start != nullptr)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			m_start[i].~T();
		}
		delete[] m_start;
	}

	m_start = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template<typename T>
T& CMyArray<T>::operator[](size_t index)
{
	if (index >= m_capacity)
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_start[index];
}

template<typename T>
const T& CMyArray<T>::operator[](size_t index) const
{
	if (index >= m_capacity)
	{
		throw std::out_of_range("Index is out of range");
	}

	return m_start[index];
}

template<typename T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray& other)
{
	if (this != &other)
	{
		if (m_capacity >= other.m_size && m_start != nullptr)
		{
			std::destroy_n(m_start, m_size + 1);
			std::uninitialized_copy_n(other.m_start, m_size + 1, m_start);
			m_size = other.m_size;
		}
		else
		{
			CMyArray<T> copy{ other };
			std::swap(m_size, copy.m_size);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_start, copy.m_start);
		}
	}
	return *this;
}

template<typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray&& other)
{
	if (this != &other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_start, other.m_start);
	}
	return *this;
}

template<typename T>
T* CMyArray<T>::begin()
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("Array is empty");
	}
	return m_start;
}

template<typename T>
const T* CMyArray<T>::cbegin() const
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("Array is empty");
	}
	return m_start;
}

template<typename T>
T* CMyArray<T>::end()
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("Array is empty");
	}
	return m_start + m_size;
}

template<typename T>
const T* CMyArray<T>::cend() const
{
	if (m_start == nullptr)
	{
		throw std::out_of_range("Array is empty");
	}
	return m_start + m_size;
}

template<typename T>
std::reverse_iterator<T*> CMyArray<T>::rbegin()
{
	return std::reverse_iterator<T*>(end());
}

template<typename T>
std::reverse_iterator<const T*> CMyArray<T>::crbegin() const
{
	return std::reverse_iterator<const T*>(cend());
}

template<typename T>
std::reverse_iterator<T*> CMyArray<T>::rend()
{
	return std::reverse_iterator<T*>(begin());
}

template<typename T>
std::reverse_iterator<const T*> CMyArray<T>::crend() const
{
	return std::reverse_iterator<const T*>(cbegin());
}
