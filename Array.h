#pragma once
#include <initializer_list>

template <class value_type> class Array {
public:
	typedef value_type* Iterator;

	Array(size_t = minsize);
	Array(const Array&);
	Array(const std::initializer_list<value_type>&);
	Array(Iterator, Iterator);
	~Array();

	Array& operator=(const Array&);
	value_type& operator[](size_t);

	Iterator begin() const { return m_elements; }
	Iterator end()   const { return (m_elements + m_size); }

	size_t size() const;
	size_t capacity() const;

	void pop_back();
	void push_back(value_type);

	void print() const;

private:
	static size_t    minsize;     // минимально выделяемый блок памяти
	static size_t    maxsize;     // максимально допустимый размер блока памяти
	value_type*      m_elements;  // указатель на блок элементов массива
	size_t           m_allocsize; // размер выделеного в куче блока памяти
	size_t           m_size;      // размер рабочей области массива

	void allocate(size_t);
	void free();
	void resize(size_t);

};

#include "Array.inl"