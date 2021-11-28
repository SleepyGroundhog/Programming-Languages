#include "List-Iterator.h"

template <class T>
typename List<T>::Iterator
List<T>::begin() const {
	return List<T>::Iterator(m_first);
}

template <class T>
typename List<T>::Iterator
List<T>::end() const {
	m_end->m_prev = m_last;
	return List<T>::Iterator(m_end);
}

template <class T>
List<T>::Iterator::Iterator(Node<T>* node) {
	m_selected_node = node;
}

template <class T>
List<T>::Iterator::Iterator(const Iterator& iterator) {
	*this = iterator;
}

template <class T>
typename List<T>::Iterator&
List<T>::Iterator::operator=(const Iterator& iterator) {
	if (this != &iterator)
		m_selected_node = iterator.m_selected_node;
	return *this;
}

template <class T>
typename List<T>::Iterator&
List<T>::Iterator::operator++() {
	if (m_selected_node->m_next == 0)
		throw (std::logic_error( "list iterator out of range" ));
	m_selected_node = m_selected_node->m_next;
	return *this;
}

template <class T>
typename List<T>::Iterator
List<T>::Iterator::operator++(int) {
	List<T>::Iterator temp(*this);
	++(*this);
	return temp;
}

template <class T>
typename List<T>::Iterator&
List<T>::Iterator::operator--() {
	if (m_selected_node->m_prev == 0)
		throw (std::logic_error("list iterator out of range"));
	m_selected_node = m_selected_node->m_prev;
	return *this;
}

template <class T>
typename List<T>::Iterator
List<T>::Iterator::operator--(int) {
	List<T>::Iterator temp(*this);
	--(*this);
	return temp;
}

template <class T>
typename List<T>::Iterator&
List<T>::Iterator::operator+=(size_t count) {
	*this = *this + count;
	return *this;
}

template <class T>
typename List<T>::Iterator
List<T>::Iterator::operator+(size_t count) {
	List<T>::Iterator temp = *this;
	for (int i = 0; i < count; ++i)
		++temp;
	return temp;
}

template <class T>
typename List<T>::Iterator&
List<T>::Iterator::operator-=(size_t count) {
	*this = *this - count;
	return *this;
}

template <class T>
typename List<T>::Iterator
List<T>::Iterator::operator-(size_t count) {
	List<T>::Iterator temp = *this;
	for (int i = 0; i < count; ++i)
		--temp;
	return temp;
}

template <class T>
T&
List<T>::Iterator::operator*() {
	return m_selected_node->m_value;
}

template <class T>
bool
List<T>::Iterator::operator!=(const typename List<T>::Iterator& right) const {
	if (m_selected_node == 0 || right.m_selected_node == 0)
		return true;
	return m_selected_node != right.m_selected_node;
}