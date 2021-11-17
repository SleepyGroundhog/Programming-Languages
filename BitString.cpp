#include "BitString.h"

BitString::BitString(int size) : Array(size) {}
BitString::BitString(string str) { fromString(str); }

void BitString::fromString(string str) {
	for (int i = 0; i < (int)str.size(); ++i) {
		m_data[i] = str[i] - '0';
	}
	m_size = str.size();
}

BitString BitString::operator~() {
	for (int i = 0; i < this->size(); ++i)
		this->m_data[i] = !this->m_data[i];
	return *this;
}

BitString BitString::operator&(const BitString& right) {
	BitString left = *this;
	error(left.size() != right.size(), 3, "diffirent sizes");
	for (int i = 0; i < max(left.size(), right.size()); ++i)
		left.m_data[i] = left.m_data[i] && right.m_data[i];
	return left;
}

BitString BitString::operator+(const BitString& right) {
	BitString left = *this;
	error(left.size() != right.size(), 3, "diffirent sizes");
	for (int i = 0; i < max(left.size(), right.size()); ++i)
		left.m_data[i] = left.m_data[i] || right.m_data[i];
	return left;
}

BitString BitString::operator^(const BitString& right) {
	BitString left = *this;
	error(left.size() != right.size(), 3, "diffirent sizes");
	for (int i = 0; i < max(left.size(), right.size()); ++i)
		left.m_data[i] = left.m_data[i] != right.m_data[i];
	return left;
}

BitString& BitString::operator>>(int right) {
	for (int i = size() - 1; i >= right; --i)
		m_data[i] = m_data[i - right];
	for (int i = right - 1; i >= 0; --i)
		m_data[i] = 0;
	return *this;
}

BitString& BitString::operator<<(int left) {
	for (int i = 0; i < size() - left; ++i)
		m_data[i] = m_data[i + left];
	for (int i = size() - left; i < size(); ++i)
		m_data[i] = 0;

	return *this;
}

ostream& operator<<(ostream& out, const BitString& right) {
	for (int i = 0; i < right.size(); ++i)
		out << (int)right[i];
	return out;
}

istream& operator>>(istream& in, BitString& right) {
	string str;
	in >> str;
	right.fromString(str);
	return in;
}

BitString& BitString::operator=(const BitString& right) {
	if (this != &right) {
		if (right.size() < m_size) {
			for (int idx = right.size(); idx < m_size; ++idx) {
				m_data[idx] = 0;
			}
		}
		m_size = right.size();
		for (int idx = 0; idx < size(); ++idx)
			m_data[idx] = right[idx];
		m_size = right.m_size;
	}
	return *this;
}

void BitString::print() const {
	cout << *this;
}