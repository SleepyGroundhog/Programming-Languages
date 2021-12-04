#pragma once
#include <cassert>
#include <stdexcept>
#include <iostream>

template <class value_t>
class List {
private:
	class Node;
public:
	class Iterator;           

	List() : head(new Node), tail(new Node), count (0) {
		tail->prev = head;
		head->next = tail;
	}

	List(const List& list) : List() { *this = list; }

	List(const List::Iterator& begin, const List::Iterator& end)
		: List() {
		Iterator it = begin;
		while ( it != end ) {
			push_back( *it );
			++it;
		}
	}

	~List() {
		clear();
		delete tail;
		delete head;
	}

	List& operator=(const List& list) {
		if (this != &list) {
			clear();
			for (auto element : list) {
				push_back(element);
			}
		}
		return *this;
	}

	bool isEmpty() { return count == 0; }
	
	size_t size() const { return count; }

	void clear() { while ( !isEmpty() ) pop_back(); }

	void push_front(value_t new_element) {
		Node* new_node = new Node(new_element);
		link_node(new_node, head, head->next);
		++count;
	}

	void push_back(value_t new_element) {
		Node* new_node = new Node(new_element);
		link_node(new_node, tail->prev, tail);
		++count;
	}

	void pop_back() {
		if ( isEmpty() ) throw (std::out_of_range("empty list deleting"));
		remove ( tail->prev );
		--count;
	}

	void pop_front() {
		if ( isEmpty() ) throw (std::out_of_range("empty list deleting"));
		remove ( head->next );
		--count;
	}

	void print(bool newline = true) {
		if ( isEmpty() ) std::cout << "list is empty";
		for (auto& element : *this) {
			std::cout << element << " ";
		}
		if (newline) std::cout << "\n";
	}

	Iterator begin() const { return Iterator(head->next); }
	Iterator end()   const { return Iterator(tail); }

private:
	Node*   head;   // fictitious element to mark list begin
	Node*   tail;   // fictitious element to mark list end
	size_t  count;  // used for counting list nodes

	void link_node(Node* node, Node* prev, Node* next) {
		assert(prev->next == next && next->prev == prev && "Nodes is not adjacent - memory leaking");
		node->next = next;
		node->prev = prev;
		next->prev = node;
		prev->next = node;
	}

	void remove(Node* node) { // Может работать не совсем корректно
		if (node == head || node == tail) throw(std::logic_error("removing fictitiout element"));
		Node* temp = node;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete temp;
	}

	class Node {
	private:
		friend List;
		friend List::Iterator;

		value_t  value;
		Node*    next;
		Node*    prev;
		Node(value_t value) : Node() { this->value = value; }
		Node() : next(0), prev(0) {}

	};
	
};


template <class value_t>
class List<value_t>::Iterator {
	friend class List;
public:
	Iterator(const Iterator& iterator) { *this = iterator; }
	Iterator& operator=(const Iterator& iterator) { if (this != &iterator) { it = iterator.it; } return *this; }

	Iterator& operator++() {
		if (it->next == 0) { // if it is fictitious element
			throw (std::out_of_range("list out of range"));
		}
		it = it->next;
		return *this;
	}

	Iterator  operator++(int) {
		Iterator temp(*this);
		++(*this);
		return temp;
	}

	Iterator& operator--() {
		if (it->prev == 0) { // if it is fictitious element
			throw (std::out_of_range("list out of range"));
		}
		it = it->prev;
		return *this;
	}

	Iterator  operator--(int) {
		Iterator temp(*this);
		--(*this);
		return temp;
	}

	Iterator  operator+(size_t count) {
		Iterator temp = *this;
		for (int i = 0; i < count; ++i) ++temp;
		return temp;
	}

	Iterator  operator-(size_t count) {
		Iterator temp = *this;
		for (int i = 0; i < count; ++i) --temp;
		return temp;
	}

	Iterator& operator+=(size_t count) { *this = *this + count; return *this; }
	Iterator& operator-=(size_t count) { *this = *this - count; return *this; }
	value_t& operator*() { return it->value; }
	bool operator!=(const Iterator& right) const { return it != right.it; }

private:
	Iterator(Node* node) { it = node; }
	Node* it;

};