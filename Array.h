#pragma once
#include <initializer_list>

// ����� ����������� �������� ������������ ������
//

template <class value_type> class Array {
public:
	using Iterator = value_type*;

	Array(size_t = minsize);                         // ����������� �� ������� / �� ���������
	Array(const Array&);                             // ����������� ��������� �����������
	Array(const std::initializer_list<value_type>&); // ����������� ��� uniform-�������������
	Array(Iterator, Iterator);                       // ����������� ����� ��� ���������
	~Array();                                        // ����������

	Array& operator=(const Array&);     // �������� ��������� �����������
	value_type& operator[](size_t);     // �������� ���������� � ��������� ������������ ���������

	Iterator begin() const;             // ��������� �� ������ ����� ������ �������
	Iterator end() const;               // ��������� �� ����� ������� ������� �������

	size_t   size() const;              // �������� ������ ������� ������� �������
	size_t   capacity() const;          // �������� ������ ����������� � ������� ����� ������
	void     clear();                   // ������� ������ � ��������� ���� ������ �� 10 ���������
	void     resize(size_t);            // �������� ������ ����������� ����������� ����� ������

	void     pop_back();                // ������� ��������� ������� ������� ���, ���� ������ ����, ����������� ����������
	                                    // ���� std::logic_error
	void     push_back(value_type);     // ��������� ������� � ����� �������, ��� �������������� ����������� ������
	void     print(bool = true) const;  // ������� ��� �������� ������� ��� ���������, ��� ������ ����. �������� - ��������
			    					    // ������� ������ � �����

private:
	static size_t    minsize;           // ���������� ���������� ���� ������
	static size_t    maxsize;           // ����������� ���������� ������ ����� ������
	value_type*      m_elements;        // ��������� �� ���� ��������� �������
	size_t           m_allocsize;       // ������ ���������� � ���� ����� ������
	size_t           m_size;            // ������ ������� ������� �������

	void allocate(size_t);              // ��������� ��������� ������ �������
	void free();                        // ������������ ������ �������

};

#include "Array.inl"