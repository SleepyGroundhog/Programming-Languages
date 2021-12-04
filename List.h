#pragma once
#include <initializer_list>

template <class value_t> class List;

template <class value_t> class List {
public:
	class Node {
		friend List<value_t>;
		friend List<value_t>::Iterator;
	public:
		value_t        m_value;
		Node* m_next;
		Node* m_prev;
		Node(value_t value) : Node() { m_value = value; }
	private:
		Node() : m_next(0), m_prev(0) {}
	};

	class Iterator;           

	List();
	List(const List&);
	List(const std::initializer_list<value_t>&);
	List(const List<value_t>::Iterator&, const List<value_t>::Iterator&);
	
	~List();

	List& operator=(const List&);

	size_t size() const;
	void   clear();

	void pop_back();         
	void push_back(value_t); 
	void print(bool = true); 	 

	Iterator begin() const;
	Iterator end() const;

private:
	Node*   m_first;    
	Node*   m_last;     
	Node*   m_end;      
	size_t  m_size;  
	
};

#include "List.inl"

