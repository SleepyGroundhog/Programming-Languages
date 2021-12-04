#pragma once
#include "List.h"

template <class value_t> class List<value_t>::Iterator {
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
	value_t& operator*();

	bool operator!=(const List<value_t>::Iterator&) const;

private:
	Iterator(Node*);
	Node* m_selected_node;
};

#include "List-Iterator.inl"