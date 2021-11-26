#pragma once
#include "List.h"

template <class T> class List<T>::Iterator {
	friend class List;
public:
	Iterator(const Iterator&);
	Iterator& operator=(const Iterator&);
	Iterator& operator++();
	Iterator  operator++(int);
	Iterator& operator--();
	Iterator  operator--(int);
	Iterator  operator+(size_t);
	Iterator  operator-(size_t);
	Iterator& operator+=(size_t);
	Iterator& operator-=(size_t);
	T& operator*();

	bool operator!=(const List<T>::Iterator&) const;

private:
	Iterator(Node<T>*);
	Node<T>* m_selected_node;
};

#include "List-Iterator.inl"