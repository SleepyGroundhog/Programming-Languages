#include "Array.h"

void error(bool condition, int code, string msg) {
	if (condition) {
		cerr << msg;
		exit(code);
	}
}

void Array::init() {
	for (int idx = 0; idx < MAX_SIZE + 1; ++idx)
		m_data[idx] = 0;
}

bool Array::range(int value, int begin, int end) {
	return (begin <= value && value < end);
}


Array::Array(int size) : m_size(size), m_data(nullptr) {
	if (m_data == nullptr) {
		m_data = new char[MAX_SIZE + 1];
	}
	init();
}

Array::Array(const Array& a) : m_size(0), m_data(nullptr) {
	if (m_data == nullptr) {
		m_data = new char[MAX_SIZE + 1];
	}
	init();
	*this = a;
}

Array::~Array() {
	if (m_data != nullptr) {
		delete[] m_data;
	}
}

int Array::size() const {
	return m_size;
}

Array& Array::operator=(const Array& a) {
	if (this != &a) {
		if (a.size() < m_size) {
			for (int idx = a.size(); idx < m_size; ++idx) {
				m_data[idx] = 0;
			}
		}
		m_size = a.size();
		for (int idx = 0; idx < size(); ++idx)
			m_data[idx] = a[idx];
		m_size = a.m_size;
	}
	return *this;
}

char& Array::operator[](int idx) const {
	error(!range(idx, 0, size()), 3, "out of range");
	return m_data[idx];
}

ostream& operator<<(ostream& out, const Array& right) {
	for (int i = 0; i < right.size(); ++i)
		out << (int)right[i] << " ";
	return out;
}

istream& operator>>(istream& in, const Array& right) {
	for (int i = 0; i < right.m_size; ++i) {
		in >> right[i];
		right[i] -= '0';
	}
	return in;
}


Array* Array::operator+(const Array& right) const {
	Array* result;
	result = new Array(max(size(), right.size()));
	for (int i = 0; i < result->size(); ++i)
		result->m_data[i] = m_data[i] + right.m_data[i];
	return result;
}

void Array::print() const {
	cout << *this;
}