#pragma once

#include <iterator>
#include <string>
#include <memory>
#include <stdexcept>

class CStringList
{
public:
	// Конструкторы

	CStringList();
	CStringList(const CStringList& other);
	CStringList(CStringList&& other) noexcept;

	// Операторы присваивания

	CStringList& operator=(const CStringList& other);
	CStringList& operator=(CStringList&& other) noexcept;

	// Деструктор

	~CStringList() noexcept;

	// Вставка

	void PushBack(const std::string& str);
	void PushFront(const std::string& str);

	// Очистка
	void Clear();

	// Получение размера списка
	size_t Size();

	// Итераторы

	std::string* begin();
	const std::string* cbegin() const;
	std::string* end();
	const std::string* cend() const;
	
	std::reverse_iterator<std::string*> rbegin();
	std::reverse_iterator<const std::string*> crbegin() const;
	std::reverse_iterator<std::string*> rend();
	std::reverse_iterator<const std::string*> crend() const;
private:
	void Allocate(size_t size);

	std::string* m_start;

	size_t m_size;	
};
