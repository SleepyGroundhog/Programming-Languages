#include "BitString.h"

BitString::BitString(int size) : Array(size) {}

BitString operator~(BitString right) {
	for (int i = 0; i < right.size(); ++i)
		right.m_data[i] = !right.m_data[i];
	return right;
}

BitString operator&(BitString left, const BitString& right) {
	error(left.size() != right.size(), 3, "diffirent sizes");
	for (int i = 0; i < max(left.size(), right.size()); ++i)
		left.m_data[i] = left.m_data[i] && right.m_data[i];
	return left;
}

BitString operator|(BitString left, const BitString& right) {
	error(left.size() != right.size(), 3, "diffirent sizes");
	for (int i = 0; i < max(left.size(), right.size()); ++i)
		left.m_data[i] = left.m_data[i] || right.m_data[i];
	return left;
}

BitString operator^(BitString left, const BitString& right) {
	error(left.size() != right.size(), 3, "diffirent sizes");
	for (int i = 0; i < max(left.size(), right.size()); ++i)
		left.m_data[i] = left.m_data[i] != right.m_data[i];
	return left;
}

BitString& BitString::operator>>(int x) {
	for (int i = size() - 1; i >= x; --i)
		m_data[i] = m_data[i - x];
	for (int i = x - 1; i >= 0; --i)
		m_data[i] = 0;
	return *this;
}

BitString& BitString::operator<<(int x) {
	for (int i = 0; i < size() - x; ++i)
		m_data[i] = m_data[i + x];
	for (int i = size() - x; i < size(); ++i)
		m_data[i] = 0;

	return *this;
}

ostream& operator<<(ostream& output, const BitString& right) {
	for (int i = 0; i < right.size(); ++i)
		output << (int)right[i];
	return output;
}

istream& operator>>(istream& input, BitString& right) {
	string temp;
	input >> temp;
	for (int i = 0; i < (int)temp.size(); ++i) {
		right.m_data[i] = temp[i] - '0';
	}
	right.m_size = temp.size();
	return input;
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