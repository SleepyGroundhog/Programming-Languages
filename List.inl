#include "List.h"
#include "List-Iterator.h"

#include <stdexcept>
#include <iostream>

// Конструкторы класса Node

template <class T> Node<T>::Node()
	: m_next(0), m_prev(0) {}

template <class T> Node<T>::Node( T value )
	: Node() {
	m_value = value;
}



// Конструкторы, деструктор и оператор= класса List

template <class T> List<T>::List()
	: m_end(new Node<T>), m_first(m_end), m_last(m_end), m_iterator(0), m_size(0) {}

template <class T> List<T>::List(const List& list) : List() {
	*this = list;
}

template <class T> List<T>::List(const std::initializer_list<T>& uniform_list) : List() { 
	for (auto& element : uniform_list) push_back(element);
}

template <class T> List<T>::List(const List<T>::Iterator& first, const List<T>::Iterator& last) : List() {
	List<T>::Iterator it = first;
	while (it != last) {
		push_back(*it);
		++it;
	}
}


template <class T> List<T>& List<T>::operator=(const List& list) {
	if (this != &list) {
		clear();
		Node<T>* current = list.m_first;
		while (current != 0) {
			push_back(current->m_value);
			current = current->m_next;
		}
		m_size = list.size();
	}
	return *this;
}



// Функциональные методы

template <class T> size_t List<T>::size() const { return m_size; }

template <class T> void List<T>::clear() {
	while (size() != 0) {
		pop_back();
	}
}

template <class T> void List<T>::pop_back() {
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

template <class T> void List<T>::push_back(T new_element) {
	Node<T>* new_node = new Node<T>(new_element);
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

template <class T> void List<T>::print(bool newline) {
	if (size() == 0) std::cout << "list is empty";
	for (auto& element : *this)
		std::cout << element << " ";
	if (newline) std::cout << "\n";
}

template <class T> List<T>::~List() { clear(); delete m_end; }



// Методы для выполнения перемещения по списку (методы-итераторы)

template <class T> T* List<T>::iter() {
	if (m_iterator == 0) m_iterator = m_first;
	return &m_iterator->m_value;
}

template <class T> void List<T>::first() { m_iterator = m_first; }

template <class T> void List<T>::last()  { m_iterator = m_last; }

template <class T> void List<T>::next()  { m_iterator = m_iterator->m_next; }

template <class T> void List<T>::prev()  { m_iterator = m_iterator->m_prev; }

template <class T> void List<T>::skip(int count) {
	if (count >= 0) while (count != 0) { next(); --count; }
	else while (count != 0) { prev(); ++count; }
}


