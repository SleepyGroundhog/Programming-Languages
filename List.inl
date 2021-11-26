#include "List.h"
#include <stdexcept>
#include <iostream>

// Конструкторы класса Node

template <class T> Node<T>::Node() : m_next(0), m_prev(0) {}

template <class T> Node<T>::Node( T value ) : Node() { m_value = value; }




// Конструкторы и деструктор класса List

template <class T> List<T>::List() : m_first(0), m_last(0), m_current(0), m_size(0), m_end(new Node<T>) {}

template <class T> List<T>::List(const List& list) : List() { *this = list; }

template <class T> List<T>::List(const std::initializer_list<T>& uniform_list) : List() { 
	for (auto& element : uniform_list) push_back(element);
}



// Перегрузка операторов для класса List

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
		m_first = m_last = 0;
		m_last->m_next = m_end;
	} else {
		m_last = m_last->m_prev;
		delete m_last->m_next;
		m_last->m_next = 0;
	}
	--m_size;
}

template <class T> void List<T>::push_back(T new_element) {
	Node<T>* new_node = new Node<T>(new_element);
	if (m_size == 0) {
		m_first = m_last = new_node;
		m_first->m_next = 0;
		m_first->m_prev = 0;
	} else {
		new_node->m_prev = m_last;
		m_last = new_node;
		m_last->m_next = 0;
	}
	++m_size;
}
/*
template <class T> void List<T>::print(bool newline) {
	if (size() == 0) std::cout << "list is empty";
	else if (size() == 1) std::cout << m_first->m_value;
	else {
		Node<T>* saved_current = m_current;
		Node<T>* current = m_first;
		first();
		for (unsigned i = 0; i < size(); ++i) {
			std::cout << *iter() << " ";
			next();
		}
		m_current = saved_current;
	}
	if (newline) std::cout << "\n";
}
*/
template <class T> List<T>::~List() { clear(); }



// Методы для выполнения перемещения по списку (методы-итераторы)
/*
template <class T> T* List<T>::iter() {
	if (m_current == 0) m_current = m_first;
	return &m_current->m_value;
}

template <class T> void List<T>::first() { m_current = m_first; }

template <class T> void List<T>::last() { m_current = m_last; }

template <class T> void List<T>::next() { m_current = m_current->m_next; }

template <class T> void List<T>::prev() { m_current = m_current->m_prev; }

template <class T> void List<T>::skip(int count) {
	if (count >= 0) while (count != 0) { next(); --count; }
	else while (count != 0) { prev(); ++count; }
}
*/
template <class T> typename List<T>::Iterator List<T>::begin() const {
	return List<T>::Iterator(m_first);
}

template <class T> typename List<T>::Iterator List<T>::end() const {
	return List<T>::Iterator(0);
}


// Методы и конструкторы вложенного класса Iterator

template <class T> List<T>::Iterator::Iterator(Node<T>* node) {  m_selected_node = node; }

template <class T> List<T>::Iterator::Iterator(const Iterator& iterator) { *this = iterator; }

template <class T> typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& iterator) {
	if (this != &iterator)
		m_selected_node = iterator.m_selected_node;
	return *this;
}

template <class T> typename List<T>::Iterator& List<T>::Iterator::operator++() {
	m_selected_node = m_selected_node->m_next;
	return *this;
}

template <class T> typename List<T>::Iterator List<T>::Iterator::operator++(int) {
	List<T>::Iterator temp(*this);
	m_selected_node = m_selected_node->m_next;
	return temp;
}

template <class T> typename List<T>::Iterator& List<T>::Iterator::operator--() {
	m_selected_node = m_selected_node->m_prev;
	return *this;
}

template <class T> typename List<T>::Iterator List<T>::Iterator::operator--(int) {
	List<T>::Iterator temp(*this);
	m_selected_node = m_selected_node->m_prev;
	return temp;
}

template <class T> typename List<T>::Iterator& List<T>::Iterator::operator+=(size_t count) {
	for (int i = 0; i < count; ++i)
		++(*this);
	return *this;
}

template <class T> typename List<T>::Iterator& List<T>::Iterator::operator-=(size_t count) {
	for (int i = 0; i < count; ++i)
		--(*this);
	return *this;
}

template <class T> T& List<T>::Iterator::operator*() {
	return m_selected_node->m_value;
}

template <class T> bool List<T>::Iterator::operator!=(const typename List<T>::Iterator& right) const {
	return m_selected_node != right.m_selected_node;
}