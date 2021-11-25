#pragma once

template <class T> class Array {
public:
	using iterator = T*;

	Array(size_t);
	Array(const Array&);

	//Array(iterator, iterator);
	
	~Array();

	Array& operator=(const Array&);
	//T& operator[](size_t);

	


	iterator begin() const { return m_elements; }
	iterator end() const   { return (m_elements + m_size); }

	size_t size() const;
	size_t capacity() const;

	void pop_back();
	void push_back(T);

	
	

private:
	static size_t    maxsize;     // ������������ ���������� ������ ������� - 100 ���������
	T*               m_elements;  // ��������� �� ���� ��������� �������
	size_t           m_allocsize; // ������ ���������� ������
	size_t           m_size;      // ������ ������� ������� �������

	void reallocate(size_t);
	void free();


};

#include "Array.inl"