#include "List.h"

#include <stdexcept>
#include <iostream>


template <class value_t>
List<value_t>::

List(const List<value_t>::Iterator& first, const List<value_t>::Iterator& last)
	: List() {
	List<value_t>::Iterator it = first;
	while (it != last) {
		push_back(*it);
		++it;
	}
}


template <class value_t> List<value_t>& List<value_t>::operator=(const List& list) {
	if (this != &list) {
		clear();
		Node* current = list.head;
		while (current != 0) {
			push_back(current->value);
			current = current->next;
		}
		count = list.size();
	}
	return *this;
}

template <class value_t> void List<value_t>::pop_back() {
	if (count == 0) throw (std::logic_error( "empty list deleting" ));
	if (count == 1) {
		delete tail;
		head = tail = tail_next;
	} else {
		tail = tail->prev;
		delete tail->next;
		tail->next = tail_next;
	}
	--count;
}

template <class value_t> void List<value_t>::push_back(value_t new_element) {
	Node* new_node = new Node(new_element);
	new_node->next = tail_next;
	tail_next->prev = new_node;
	if (count == 0) {
		head = tail = new_node;
	} else {
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
	++count;
}

template <class value_t> void List<value_t>::print(bool newline) {
	if (size() == 0) std::cout << "list is empty";
	for (auto& element : *this)
		std::cout << element << " ";
	if (newline) std::cout << "\n";
}