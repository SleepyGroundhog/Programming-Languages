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
	
	value_type* iter();              // ���������� ��������� �� ������� ������� ������
	void first();             // ���������� �������� � ������ ������
	void last();              // ���������� �������� � ����� ������
	void next();              // ���������� �������� � ���������� �������� ���, ���� ����� ������ - � ������
	void prev();              // ���������� �������� � ����������� �������� ���, ���� ������ ������ - � �����
	void skip(int);           // ���������� �������� ������ ��� ����� �� ���������� � �������� ��������� ���������� ���������
	

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
	Node<value_type>*   m_first;     // ��������� �� ������ ���� ������
	Node<value_type>*   m_last;      // ��������� �� ��������� ���� ������
	Node<value_type>*   m_current;   // ��������� �� ���� ������ ��������������� ��������� ���������
	size_t              m_size;      // ���������� ��������� � ������

};


#include "List.inl"
