#pragma once

template <class value_t>
class List {
private:
	class Node;
public:
	class Iterator;           

	List() : tail_next(new Node), head(tail_next), tail(tail_next), count(0) {}
	List(const List& list) : List() { *this = list; }
	List(const List::Iterator&, const List::Iterator&);
    ~List() { clear(); delete tail_next; }

	List& operator=(const List&);

	bool isEmpty() { return count == 0; }
	
	size_t size() const { return count; }

	void clear() { while ( !isEmpty() ) pop_back(); }

	void pop_back();         
	void push_back(value_t); 
	void print(bool newline = true); 	 

	Iterator begin() const { return Iterator(head); }
	Iterator end() const { tail_next->prev = tail; return Iterator(tail_next); }

private:
	Node*   head;    
	Node*   tail;     
	size_t  count;  // used for counting list nodes

	// fictitious elements
	Node* tail_next;
  //Node* first_prev;

	class Node {
		friend List;
		friend List::Iterator;

	public:
		value_t  value;
		Node*    next;
		Node*    prev;
		Node(value_t value) : Node() { this->value = value; }
		Node() : next(0), prev(0) {}

	};
	
};

#include "List.inl"

template <class value_t> class List<value_t>::Iterator {
	friend class List;
public:

	Iterator(const Iterator& iterator) { *this = iterator; }
	Iterator& operator=(const Iterator& iterator) { if (this != &iterator) { it = iterator.it; } return *this; }

	Iterator& operator++() {
		if (it->next == 0) { // если it указывает на фиктивный элемент
			throw (std::logic_error("list iterator out of range"));
		}
		it = it->next;
		return *this;
	}

	Iterator  operator++(int) {
		List<value_t>::Iterator temp(*this);
		++(*this);
		return temp;
	}

	Iterator& operator--() {
		if (it->prev == 0) { // если it указывает на первый элемент
			throw (std::logic_error("list iterator out of range"));
		}
		it = it->prev;
		return *this;
	}

	Iterator  operator--(int) {
		List<value_t>::Iterator temp(*this);
		--(*this);
		return temp;
	}

	Iterator  operator+(size_t count) {
		List<value_t>::Iterator temp = *this;
		for (int i = 0; i < count; ++i)
			++temp;
		return temp;
	}

	Iterator  operator-(size_t count) {
		List<value_t>::Iterator temp = *this;
		for (int i = 0; i < count; ++i)
			--temp;
		return temp;
	}

	Iterator& operator+=(size_t count) { *this = *this + count; return *this; }
	Iterator& operator-=(size_t count) { *this = *this - count; return *this; }
	value_t& operator*() { return it->value; }

	bool operator!=(const List<value_t>::Iterator& right) const {
		if (it == 0 || right.it == 0)
			return true;
		return it != right.it;
	}

private:
	Iterator(Node* node) { it = node; }
	Node* it;
};
