#pragma once
#include <initializer_list>

template <class T> class List;

template <class T> class Node {
	friend List<T>;
public:
	T        m_value;
	Node<T>* m_next;
	Node<T>* m_prev;
	Node(T);
private:
	Node();
};

template <class T> class List {
public:
	class Iterator;           // �����-�������� ( ������ ���������� � ����� List-Iterator.inl )

	List();
	List(const List&);
	List(const std::initializer_list<T>&);
	List(const List<T>::Iterator&, const List<T>::Iterator&);
	
	~List();

	List& operator=(const List&);

	size_t size() const;
	void   clear();

	void pop_back();          // ������� ������� �� ����� ������
	void push_back(T);        // ��������� ������� � ����� ������
	void print(bool = true);  // ������� �������� ���� ��������� ������ ��� ��������� �� ������
	
	T*   iter();			  // ���������� ��������� �� ������� ������� ������
	void first();		      // ���������� �������� � ������ ������
	void last();		      // ���������� �������� � ����� ������
	void next();			  // ���������� �������� � ���������� �������� ���, ���� ����� ������ - � ������
	void prev();			  // ���������� �������� � ����������� �������� ���, ���� ������ ������ - � �����
	void skip(int);			  // ���������� �������� ������ ��� ����� �� ���������� � �������� ��������� ���������� ���������

	Iterator begin() const;
	Iterator end() const;

private:
	Node<T>*   m_first;    // ��������� �� ������ ���� ������
	Node<T>*   m_last;     // ��������� �� ��������� ���� ������
	Node<T>*   m_end;      // ��������� �� ������ ���� ��������� �� ���������
	Node<T>*   m_iterator; // ��������� �� ���� ������ ��������������� ��������� ���������
	size_t     m_size;     // ���������� ��������� � ������
	
};

#include "List.inl"

