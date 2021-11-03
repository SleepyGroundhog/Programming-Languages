#pragma once
#include <iostream>
#include <exception>

using namespace std;

template <class T>
class Array
{
protected:
	int m_size;
	T*  m_data = nullptr;

	// �������� ������ ��� ������� � �������� MAX_SIZE + 1, �������� ��� ����, ����� m_data ���� ������� ����������
	void newMemory() {
		if (m_data == nullptr) {
			m_data = new T[MAX_SIZE + 1];
		}
	}

	//  ����������� ������ �������, �������� ��� ����, ��� m_data �� �������� ������� ����������
	void deleteMemory() {
		if (m_data != nullptr) {
			delete[] m_data;
		}
	}

	// ������������� �������� ��� ����� ������� ��������� value
	void initBy(T value) {
		for (int idx = 0; idx < MAX_SIZE + 1; ++idx)
			m_data[idx] = value;
	}


	void copy(const Array& a) {
		if (this != &a) {
			resize(a.getSize());
			for (int idx = 0; idx < getSize(); ++idx)
				m_data[idx] = a[idx];
		}
	}

	bool rangeCheck(int value, int begin, int end) const {
		return (begin <= value && value < end);
	}


	// ����������, ����������� ��������� � �������� �������, ��� ������� �������� ������, �� ������� ��������� �� ��������� ������� ������� m_size.
	// �������� ������� - [0, MAX_SIZE + 1)
	T& at(int idx) const {
		if (rangeCheck(idx, 0, MAX_SIZE + 1))
			return m_data[idx];
		else
			throw out_of_range("\nArray.h : T& at(int idx) const :\n\t\t\t out of range\n");
	}

public:
	static const int MAX_SIZE = 100;

	Array(int size = 0) : m_size(size) {
		newMemory();
		initBy(0);
	}

	Array(const Array& a) {
		newMemory();
		initBy(0);
		*this = a;
	}

	~Array() {
		deleteMemory();
	}

	int getSize() const {
		return m_size;
	}

	int isEmpty() {
		return m_size == 0;
	}

	// ��������� ������� ������� �� �����. ���� ����� ������ ������, ��� ������, ����� ������� ����������, ���������� ����� ��������������� ������� ��������
	void resize(int new_size) {
		if (new_size < m_size) {
			for (int idx = new_size; idx < m_size; ++idx) {
				at(idx) = 0;
			}
		}
		m_size = new_size;
	}

	// ���������� ��������� ������������ 
	Array* operator=(const Array& a) {
		if (this != &a)
			copy(a);
		return this;
	}

	// ���������� ��������� ���������� � ��������� ����, ��� ������ ��������� � ��������� [0, m_size)
	T& operator[](int idx) const {
		if (rangeCheck(idx, 0, getSize()))
			return m_data[idx];
		else
			throw out_of_range("\nArray.h : T& operator[](int idx) const :\n\t\t\t out of range\n");
	}

	// ���������� ��������� ������ ��� �������. ������� ��� �������� ������� ����� ������
	friend ostream& operator<<(ostream& out, const Array& a) {
		for (int i = 0; i < a.m_size; ++i)
			out << a[i] << " ";
		return out;
	}

	// ���������� ��������� ����� ��� �������. ���� ���� ��������� ����� ������
	friend istream& operator>>(istream& in, const Array& a) {
		for (int i = 0; i < a.m_size; ++i) {
			in >> a[i];
		}
		return in;
	}
};