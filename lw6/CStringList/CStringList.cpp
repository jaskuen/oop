#include "CStringList.h"

CStringList::CStringList()
	: m_size(0), 
	  m_start(nullptr),
	  m_end(new Node("")) 
{
	m_start = m_end;
}


CStringList::CStringList(const CStringList& other)
	: m_size(0),
	m_start(nullptr),
	m_end(new Node(""))
{
	m_start = m_end;
	Node* ptr = other.m_start;
	while (ptr != other.m_end)
	{
		PushBack(ptr->value);
		ptr = ptr->next;
	}
}


CStringList::CStringList(CStringList&& other) noexcept
	: m_size(std::exchange(other.m_size, 0)),
	m_start(std::exchange(other.m_start, nullptr)),
	m_end(std::exchange(other.m_end, nullptr))
{
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (this != &other)
	{
		CStringList copy{ other };
		std::swap(m_size, copy.m_size);
		std::swap(m_start, copy.m_start);
		std::swap(m_end, copy.m_end);
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_start, other.m_start);
		std::swap(m_end, other.m_end);
	}
	return *this;
}

CStringList::~CStringList() noexcept
{
	Clear();
}

void CStringList::PushBack(const std::string& str)
{
	Node* newNode = new Node(str);
	newNode->prev = m_end->prev;
	newNode->next = m_end;

	if (m_end->prev)
	{
		m_end->prev->next = newNode;
	}
	else
	{
		m_start = newNode;
	}

	m_end->prev = newNode;
	m_size++;
}


void CStringList::PushFront(const std::string& str)
{
	Node* newNode = new Node(str);
	newNode->next = m_start;
	newNode->prev = nullptr;

	if (m_start != m_end)
	{
		m_start->prev = newNode;
	}
	else
	{
		m_end->prev = newNode;
	}

	m_start = newNode;
	m_size++;
}

	
void CStringList::Clear()
{
	Node* current = m_start;
	while (current != m_end)
	{
		Node* next = current->next;
		delete current;
		current = next;
		m_end->prev = nullptr;
	}

	m_start = m_end;
	m_size = 0;
}


size_t CStringList::Size()
{
	return m_size;
}

void CStringList::Insert(iterator it, const std::string& value)
{
	Node* ptr = it.current;
	Node* newNode = new Node(value);

	newNode->next = ptr;
	newNode->prev = ptr ? ptr->prev : nullptr;

	if (newNode->prev)
	{
		newNode->prev->next = newNode;
	}
	else
	{
		m_start = newNode;
	}

	if (ptr)
	{
		ptr->prev = newNode;
	}
	else
	{
		m_end->prev = newNode;
	}

	m_size++;
}

void CStringList::Insert(const_iterator it, const std::string& value)
{
	Insert(static_cast<iterator>(it), value);
}

void CStringList::Delete(iterator it)
{
	if (it.current == m_end) // Нельзя удалять фиктивный узел
	{
		throw std::out_of_range("Cannot delete end iterator");
	}

	Node* node = it.current;

	if (node->prev)
	{
		node->prev->next = node->next;
	}
	else
	{
		m_start = node->next; // Удаляется голова
	}

	if (node->next)
	{
		node->next->prev = node->prev;
	}
	else
	{
		m_end->prev = node->prev; // Удаляется хвост
	}

	delete node;
	m_size--;
}

void CStringList::Delete(const_iterator it)
{
	Delete(static_cast<iterator>(it));
}

