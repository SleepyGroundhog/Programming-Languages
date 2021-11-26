#include "List.h"
#include <stdexcept>
#include <iostream>

// Конструкторы класса Node

template <class value_type> Node<value_type>::Node() : m_next(0), m_prev(0) {}

template <class value_type> Node<value_type>::Node( value_type value ) : Node() { m_value = value; }



// Конструкторы и деструктор класса List

template <class value_type> List<value_type>::List() : m_first(0), m_last(0), m_current(0), m_size(0) {}

template <class value_type> List<value_type>::List(const List& list) : List() { *this = list; }

template <class value_type> List<value_type>::List(const std::initializer_list<value_type>& uniform_list) : List() { 
	for (auto& element : uniform_list) push_back(element);
}



// Перегрузка операторов для класса List

template <class value_type> List<value_type>& List<value_type>::operator=(const List& list) {
	if (this != &list) {
		clear();
		Node<value_type>* current = list.m_first;
		while (current != 0) {
			push_back(current->m_value);
			current = current->m_next;
		}
		m_size = list.size();
	}
	return *this;
}



// Функциональные методы

template <class value_type> size_t List<value_type>::size() const { return m_size; }

template <class value_type> void List<value_type>::clear() {
	while (size() != 0) {
		pop_back();
	}
}

template <class value_type> void List<value_type>::pop_back() {
	if (m_size == 0) throw (std::logic_error( "empty list deleting" ));
	if (m_size == 1) {
		delete m_last;
		m_first = m_last = 0;
	} else {
		Node<value_type>* new_last = m_last->m_prev;
		delete m_last;
		new_last->m_next = m_first;
		m_last = new_last;
	}
	--m_size;
}

template <class value_type> void List<value_type>::push_back(value_type new_element) {
	Node<value_type>* new_node = new Node<value_type>(new_element);
	if (m_size == 0) m_first = m_last = new_node;
	else {
		new_node->m_prev = m_last;
		m_last->m_next = new_node;
		m_last = new_node;
	}
	m_first->m_prev = m_last; // Замыкаем список для того, чтобы выполнение итераций было безопасным
	m_last->m_next = m_first;
	++m_size;
}

template <class value_type> void List<value_type>::print(bool newline) {
	if (size() == 0) std::cout << "list is empty";
	else if (size() == 1) std::cout << m_first->m_value;
	else {
		Node<value_type>* saved_current = m_current;
		Node<value_type>* current = m_first;
		first();
		for (int i = 0; i < size(); ++i) {
			std::cout << *iter() << " ";
			next();
		}
		m_current = saved_current;
	}
	if (newline) std::cout << "\n";
}

template <class value_type> List<value_type>::~List() { clear(); }



// Методы для выполнения перемещения по списку (методы-итераторы)

template <class value_type> value_type* List<value_type>::iter() {
	if (m_current == 0) m_current = m_first;
	return &m_current->m_value;
}

template <class value_type> void List<value_type>::first() { m_current = m_first; }

template <class value_type> void List<value_type>::last() { m_current = m_last; }

template <class value_type> void List<value_type>::next() { m_current = m_current->m_next; }

template <class value_type> void List<value_type>::prev() { m_current = m_current->m_prev; }

template <class value_type> void List<value_type>::skip(int count) {
	if (count >= 0) while (count != 0) { next(); --count; }
	else while (count != 0) { prev(); ++count; }
}