#include "List-Iterator.h"
#include <stdexcept>


template <class value_t>
typename List<value_t>::Iterator
List<value_t>::begin() const {
	return List<value_t>::Iterator(m_first);
}

template <class value_t>
typename List<value_t>::Iterator
List<value_t>::end() const {
	m_end->m_prev = m_last;
	return List<value_t>::Iterator(m_end);
}

template <class value_t>
List<value_t>::Iterator::Iterator(Node* node) {
	m_selected_node = node;
}

template <class value_t>
List<value_t>::Iterator::Iterator(const Iterator& iterator) {
	*this = iterator;
}

template <class value_t>
typename List<value_t>::Iterator&
List<value_t>::Iterator::operator=(const Iterator& iterator) {
	if (this != &iterator)
		m_selected_node = iterator.m_selected_node;
	return *this;
}

template <class value_t>
typename List<value_t>::Iterator&
List<value_t>::Iterator::operator++() {
	if (m_selected_node->m_next == 0)
		throw (std::logic_error( "list iterator out of range" ));
	m_selected_node = m_selected_node->m_next;
	return *this;
}

template <class value_t>
typename List<value_t>::Iterator
List<value_t>::Iterator::operator++(int) {
	List<value_t>::Iterator temp(*this);
	++(*this);
	return temp;
}

template <class value_t>
typename List<value_t>::Iterator&
List<value_t>::Iterator::operator--() {
	if (m_selected_node->m_prev == 0)
		throw (std::logic_error("list iterator out of range"));
	m_selected_node = m_selected_node->m_prev;
	return *this;
}

template <class value_t>
typename List<value_t>::Iterator
List<value_t>::Iterator::operator--(int) {
	List<value_t>::Iterator temp(*this);
	--(*this);
	return temp;
}

template <class value_t>
typename List<value_t>::Iterator&
List<value_t>::Iterator::operator+=(size_t count) {
	*this = *this + count;
	return *this;
}

template <class value_t>
typename List<value_t>::Iterator
List<value_t>::Iterator::operator+(size_t count) {
	List<value_t>::Iterator temp = *this;
	for (int i = 0; i < count; ++i)
		++temp;
	return temp;
}

template <class value_t>
typename List<value_t>::Iterator&
List<value_t>::Iterator::operator-=(size_t count) {
	*this = *this - count;
	return *this;
}

template <class value_t>
typename List<value_t>::Iterator
List<value_t>::Iterator::operator-(size_t count) {
	List<value_t>::Iterator temp = *this;
	for (int i = 0; i < count; ++i)
		--temp;
	return temp;
}

template <class value_t>
value_t&
List<value_t>::Iterator::operator*() {
	return m_selected_node->m_value;
}

template <class value_t>
bool
List<value_t>::Iterator::operator!=(const typename List<value_t>::Iterator& right) const {
	if (m_selected_node == 0 || right.m_selected_node == 0)
		return true;
	return m_selected_node != right.m_selected_node;
}