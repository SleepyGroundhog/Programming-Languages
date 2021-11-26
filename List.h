#pragma once
#include <initializer_list>

template <class value_type> class Node {
public:
	value_type        m_value;
	Node<value_type>* m_next;
	Node<value_type>* m_prev;
	
	Node(value_type);

private:
	Node();
};

template <class value_type> class List {
public:
	List();
	List(const List&);
	List(const std::initializer_list<value_type>&);
	//List(Iterator, Iterator);
	~List();

	List& operator=(const List&);
	
	//operator value_type();

	//Iterator begin() const;
	//Iterator end()   const;

	size_t size() const;
	void   clear();

	void pop_back();
	void push_back(value_type);
	void print(bool = true);
	
	value_type* iter();              // Возвращает указатель на текущий элемент списка
	void first();             // Перемещает итератор в начало списка
	void last();              // Перемещает итератор в конец списка
	void next();              // Перемещает итератор к следующему элементу или, если конец списка - к началу
	void prev();              // Перемещает итератор к предидущему элементу или, если начало списка - в конец
	void skip(int);           // Перемещает итератор вперед или назад на переданное в качестве параметра количество элементов
	

	class Iterator {
	public:
		Iterator& operator++();
		Iterator& operator++(int);
		Iterator& operator--();
		Iterator& operator--(int);
		value_type operator*();
		value_type operator->();

	private:


	};

private:
	Node<value_type>*   m_first;     // Указатель на первый узел списка
	Node<value_type>*   m_last;      // Указатель на последний узел списка
	Node<value_type>*   m_current;   // Указатель на узел списка соответствующий положению итератора
	size_t              m_size;      // Количество элементов в списке

};


#include "List.inl"
