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

	// Выделяет память для массива с размером MAX_SIZE + 1, проверяя при этом, чтобы m_data было нулевым указателем
	void newMemory() {
		if (m_data == nullptr) {
			m_data = new T[MAX_SIZE + 1];
		}
	}

	//  Освобождает память массива, проверяя при этом, что m_data не является нулевым указателем
	void deleteMemory() {
		if (m_data != nullptr) {
			delete[] m_data;
		}
	}

	// Устанавливает значение всх ячеек массива значением value
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


	// Индексация, допускающая обращение к областям массива, для которых выделена память, но которые находятся за пределами размера массива m_size.
	// Диапазон доступа - [0, MAX_SIZE + 1)
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

	// Изменение размера массива на новый. Если новый размер меньше, чем старый, часть массива отсекается, отсеченной части устанавливаются нулевые значения
	void resize(int new_size) {
		if (new_size < m_size) {
			for (int idx = new_size; idx < m_size; ++idx) {
				at(idx) = 0;
			}
		}
		m_size = new_size;
	}

	// Перегрузка оператора присваивания 
	Array* operator=(const Array& a) {
		if (this != &a)
			copy(a);
		return this;
	}

	// Перегрузка оператора индексации с проверкой того, что индекс находится в диапазоне [0, m_size)
	T& operator[](int idx) const {
		if (rangeCheck(idx, 0, getSize()))
			return m_data[idx];
		else
			throw out_of_range("\nArray.h : T& operator[](int idx) const :\n\t\t\t out of range\n");
	}

	// Перегрузка оператора вывода для массива. Выводит все элементы массива через пробел
	friend ostream& operator<<(ostream& out, const Array& a) {
		for (int i = 0; i < a.m_size; ++i)
			out << a[i] << " ";
		return out;
	}

	// Перегрузка оператора ввода для массива. Ввод всех элементов через пробел
	friend istream& operator>>(istream& in, const Array& a) {
		for (int i = 0; i < a.m_size; ++i) {
			in >> a[i];
		}
		return in;
	}
};