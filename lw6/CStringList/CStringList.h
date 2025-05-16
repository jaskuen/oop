#pragma once

#include <iterator>
#include <string>
#include <memory>
#include <stdexcept>

struct Node
{
	std::string value;
	Node* next;
	Node* prev;
		
	Node(std::string v)
		: value(v),
		  next(nullptr),
		  prev(nullptr)
	{
	}
};

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

	class iterator 
	{
	public:
		using value_type = std::string;
		using reference = std::string&;
		using pointer = std::string*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator(Node* ptr) 
			: current(ptr)
		{
		}

		reference operator*() const 
		{ 
			return current->value;
		}
		pointer operator->() const 
		{ 
			return &current->value;
		}

		iterator& operator++() 
		{
			if (current)
			{
				current = current->next;
			}
			return *this;
		}

		iterator operator++(int) 
		{
			iterator temp = *this;
			++(*this);
			return temp;
		}

		iterator& operator--()
		{
			if (current)
			{
				current = current->prev;
			}
			return *this;
		}

		iterator operator--(int)
		{
			iterator temp = *this;
			--(*this);
			return temp;
		}

		bool operator==(const iterator& other) const 
		{
			return current == other.current;
		}

		bool operator!=(const iterator& other) const 
		{
			return current != other.current;
		}

		Node* current;
	};

	class const_iterator 
	{
	public:
		using value_type = std::string;
		using reference = const std::string&;
		using pointer = const std::string*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		const_iterator(const Node* ptr) 
			: current(ptr) 
		{
		}

		reference operator*() const 
		{ 
			return current->value; 
		}
		pointer operator->() const 
		{ 
			return &current->value; 
		}

		// Для преобразования в iterator
		operator iterator() const { return iterator(const_cast<Node *>(current)); }

		const_iterator& operator++() 
		{ 
			current = current->next; 
			return *this; 
		}
		const_iterator operator++(int)
		{
			return ++(*this);
		}

		const_iterator& operator--() 
		{ 
			current = current->prev; 
			return *this; 
		}
		const_iterator operator--(int)
		{
			return --(*this);
		}

		bool operator==(const const_iterator& other) const 
		{ 
			return current == other.current; 
		}
		bool operator!=(const const_iterator& other) const 
		{ 
			return current != other.current; 
		}

		const Node* current;
	};

	iterator begin() 
	{ 
		return iterator(m_start); 
	}
	iterator end() 
	{ 
		return iterator(m_end);
	}

	const_iterator cbegin() const
	{
		return const_iterator(m_start);
	}
	const_iterator cend() const
	{
		return const_iterator(m_end);
	}
	
	std::reverse_iterator<iterator> rbegin()
	{
		return std::reverse_iterator<iterator>(end());
	}
	std::reverse_iterator<iterator> rend()
	{
		return std::reverse_iterator<iterator>(begin());
	}
	std::reverse_iterator<const_iterator> crbegin() const
	{
		return std::reverse_iterator<const_iterator>(cend());
	}
	std::reverse_iterator<const_iterator> crend() const
	{
		return std::reverse_iterator<const_iterator>(cbegin());
	}

// Вставка по итератору
	void Insert(iterator it, const std::string& value);
	void Insert(const_iterator it, const std::string& value);
	void Delete(iterator it);
	void Delete(const_iterator it);
private:
	Node* m_start;
	Node* m_end;

	size_t m_size;	
};
