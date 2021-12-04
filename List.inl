#include "List.h"
#include "List-Iterator.h"

#include <stdexcept>
#include <iostream>

// Конструкторы, деструктор и оператор= класса List

template <class value_t> List<value_t>::List()
	: m_end(new Node), m_first(m_end), m_last(m_end), m_size(0) {}

template <class value_t> List<value_t>::List(const List& list) : List() {
	*this = list;
}

template <class value_t> List<value_t>::List(const std::initializer_list<value_t>& uniform_list) : List() { 
	for (auto& element : uniform_list) push_back(element);
}

template <class value_t> List<value_t>::List(const List<value_t>::Iterator& first, const List<value_t>::Iterator& last) : List() {
	List<value_t>::Iterator it = first;
	while (it != last) {
		push_back(*it);
		++it;
	}
}


template <class value_t> List<value_t>& List<value_t>::operator=(const List& list) {
	if (this != &list) {
		clear();
		Node* current = list.m_first;
		while (current != 0) {
			push_back(current->m_value);
			current = current->m_next;
		}
		m_size = list.size();
	}
	return *this;
}



// Функциональные методы

template <class value_t> size_t List<value_t>::size() const { return m_size; }

template <class value_t> void List<value_t>::clear() {
	while (size() != 0) {
		pop_back();
	}
}

template <class value_t> void List<value_t>::pop_back() {
	if (m_size == 0) throw (std::logic_error( "empty list deleting" ));
	if (m_size == 1) {
		delete m_last;
		m_first = m_last = m_end;
	} else {
		m_last = m_last->m_prev;
		delete m_last->m_next;
		m_last->m_next = m_end;
	}
	--m_size;
}

template <class value_t> void List<value_t>::push_back(value_t new_element) {
	Node* new_node = new Node(new_element);
	new_node->m_next = m_end;
	m_end->m_prev = new_node;
	if (m_size == 0) {
		m_first = m_last = new_node;
	} else {
		m_last->m_next = new_node;
		new_node->m_prev = m_last;
		m_last = new_node;
	}
	++m_size;
}

template <class value_t> void List<value_t>::print(bool newline) {
	if (size() == 0) std::cout << "list is empty";
	for (auto& element : *this)
		std::cout << element << " ";
	if (newline) std::cout << "\n";
}

template <class value_t> List<value_t>::~List() { clear(); delete m_end; }