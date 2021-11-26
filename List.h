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
	class Iterator;           // Класс-итератор ( полное объявление в файле List-Iterator.inl )

	List();
	List(const List&);
	List(const std::initializer_list<T>&);
	List(const List<T>::Iterator&, const List<T>::Iterator&);
	
	~List();

	List& operator=(const List&);

	size_t size() const;
	void   clear();

	void pop_back();          // Удаляет элемент из конца списка
	void push_back(T);        // Добавляет элемент в конец списка
	void print(bool = true);  // Выводит значения всех элементов списка или сообщение об ошибке
	
	T*   iter();			  // Возвращает указатель на текущий элемент списка
	void first();		      // Перемещает итератор в начало списка
	void last();		      // Перемещает итератор в конец списка
	void next();			  // Перемещает итератор к следующему элементу или, если конец списка - к началу
	void prev();			  // Перемещает итератор к предидущему элементу или, если начало списка - в конец
	void skip(int);			  // Перемещает итератор вперед или назад на переданное в качестве параметра количество элементов

	Iterator begin() const;
	Iterator end() const;

private:
	Node<T>*   m_first;    // Указатель на первый узел списка
	Node<T>*   m_last;     // Указатель на последний узел списка
	Node<T>*   m_end;      // Указатель на пустой узел следующий за последним
	Node<T>*   m_iterator; // Указатель на узел списка соответствующий положению итератора
	size_t     m_size;     // Количество элементов в списке
	
};

#include "List.inl"

