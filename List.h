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
	List();
	List(const List&);
	List(const std::initializer_list<T>&);
	//List(Iterator, Iterator);
	~List();

	List& operator=(const List&);

	size_t size() const;
	void   clear();

	void pop_back();          // ������� ������� �� ����� ������
	void push_back(T);        // ��������� ������� � ����� ������
	void print(bool = true);  // ������� �������� ���� ��������� ������ ��� ��������� �� ������
	
	/*
	T* iter();			      // ���������� ��������� �� ������� ������� ������
	void first();		      // ���������� �������� � ������ ������
	void last();		      // ���������� �������� � ����� ������
	void next();			  // ���������� �������� � ���������� �������� ���, ���� ����� ������ - � ������
	void prev();			  // ���������� �������� � ����������� �������� ���, ���� ������ ������ - � �����
	void skip(int);			  // ���������� �������� ������ ��� ����� �� ���������� � �������� ��������� ���������� ���������
	*/


	// �����-�������� ��� ������ List
	class Iterator {
		friend class List;
	public:
		Iterator(const Iterator&);
		Iterator& operator=(const Iterator&);
		Iterator& operator++();
		Iterator  operator++(int);
		Iterator& operator--();
		Iterator  operator--(int);
		Iterator& operator+=(size_t);
		Iterator& operator-=(size_t);
		T& operator*();

		bool operator!=(const List<T>::Iterator&) const;

	private:
		Iterator(Node<T>*);
		Node<T>* m_selected_node;
	};

	Iterator begin() const;
	Iterator end() const;

private:
	Node<T>*   m_first;    // ��������� �� ������ ���� ������
	Node<T>*   m_last;     // ��������� �� ��������� ���� ������
	Node<T>*   m_end;
	Node<T>*   m_current;  // ��������� �� ���� ������ ��������������� ��������� ���������
	size_t     m_size;     // ���������� ��������� � ������
};


#include "List.inl"
