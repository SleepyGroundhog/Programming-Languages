#include "Money.h"
using namespace std;

Money::Money() : Array(), m_point_pos(2) { m_size = 1; }
Money::Money(const Money& money) : Array() { *this = money; }
Money::Money(const string str) : Array() { fromString(str); }
Money::~Money() {}
void Money::removeLeadingZeros() { while (m_data[size() - 1] == 0 && size() > 1) m_data[--m_size] = 0; }
bool operator==(const Money& left, const Money& right) { return Money::compare(left, right) == 0; }
istream& operator>>(istream& in, Money& a) { string buf; in >> buf; a.fromString(buf); return in; }

int Money::compare(const Money& left, const Money& right) {
	for (int idx = max(left.size(), right.size()) - 1; idx >= 0; --idx)
		     if (left.m_data[idx] > right.m_data[idx])	return 1;
		else if (left.m_data[idx] < right.m_data[idx])  return -1;
														return 0;
}

Money& Money::operator=(const Money& right) {
	if (this != &right) {
		if (right.size() < m_size)
			for (int idx = right.size(); idx < m_size; ++idx)
				m_data[idx] = 0;
		m_size = right.size();
		for (int idx = 0; idx < size(); ++idx)
			m_data[idx] = right[idx];
		m_point_pos = right.m_point_pos;
	}
	return *this;
}

string Money::toString() const {
	stringstream buf;
	for (int idx = size() - 1; idx >= 0; --idx)
		buf << (int)m_data[idx];
	string result = buf.str();
	while (result.size() < 3)
		result.insert(0, "0");
	result.insert(result.size() - m_point_pos, ",");
	return result;
}

void Money::fromString(string str) {
	if (str == "0") { *this = Money(); return; }
	error(!regex_match(str.data(), regex(R"(\d{1,100},\d{2})")), 3, "string can't be converted to Money");
	str.erase(str.size() - 3, 1);
	if ((int)str.size() < m_size)
		for (int idx = str.size(); idx < m_size; ++idx)
			m_data[idx] = 0;
	m_size = str.size();
	for (int idx = 0; idx < size(); ++idx)
		m_data[idx] = str[str.size() - 1 - idx] - '0';
}

Money& Money::rightShift(int right) {
	if (*this == Money()) return *this;
	for (int idx = size() - 1; idx >= 0; --idx) m_data[idx + right] = m_data[idx];
	for (int idx = 0; idx < right; ++idx) m_data[idx] = 0;
	m_size += right;
	return *this;
}

Money& Money::leftShift(int right) {
	if (*this == Money()) return *this;
	for (int idx = 0; idx < size(); ++idx) m_data[idx] = m_data[idx + right];
	for (int idx = size() - right; idx < size(); ++idx) m_data[idx] = 0;
	m_size -= right;
	return *this;
}

Money Money::operator+(const Money& right) const {
	Money result, left(*this);
	int max = (left.m_size >= right.m_size ? left.m_size : right.m_size);
	for (int idx = 0; idx < max; ++idx) {
		result.m_data[idx] += left.m_data[idx] + right.m_data[idx];
		result.m_data[idx + 1] += result.m_data[idx] / Money::m_base;
		result.m_data[idx] %= Money::m_base;
	}
	error(result.m_data[Money::MAX_SIZE] != 0, 3, "money unsigned int addition overflow");
	result.m_size = (result.m_data[max] == 0 ? max : max + 1);
	return result;
}

Money Money::operator-(const Money& right) const {
	Money result, left(*this);
	if (Money::compare(left, right) == -1) {
		cerr << "warning: left - right < 0, return 0\n";
		return result;
	}
	for (int idx = 0; idx < left.size() + 1; ++idx) {
		result.m_data[idx] += left.m_data[idx] - right.m_data[idx];
		if (result.m_data[idx] < 0) {
			result.m_data[idx] += Money::m_base;
			result.m_data[idx + 1] -= 1;
		}
	}
	result.m_size = left.size();
	result.removeLeadingZeros();
	return result;
}

Money Money::operator*(const Money& right) const {
	Money result, left(*this);
	for (int idx = right.size() - 1; idx >= 0; --idx) {
		result.rightShift(1);
		result = result + left * right.m_data[idx];
	}
	if (result.m_data[1] >= 5)
		result = result + Money("0,01").rightShift(2);
	result.leftShift(2);
	result.m_point_pos = 2;
	return result;
}

Money operator*(const Money& left, const char right) {
	Money result;
	for (int idx = 0; idx < left.size(); ++idx) {
		result.m_data[idx] += (left.m_data[idx] * right);
		result.m_data[idx + 1] += result.m_data[idx] / Money::m_base;
		result.m_data[idx] %= Money::m_base;
	}
	result.m_size = (result.m_data[left.size()] == 0 ? left.size() : left.size() + 1);
	result.removeLeadingZeros();
	return result;
}

Money Money::operator/(Money right)  const {
	Money result, left(*this);
	error(right == Money() || right == Money("0,00"), 3, "division by zero");
	if ((Money::compare(left.rightShift(5), right.rightShift(2)) == -1)) {
		return result;
	}
	error(right == Money(), 3, "division by zero");
	Money sub;
	for (int i = 0; left.size() - i >= 0; ++i) {
		sub.rightShift(1);
		sub.m_data[0] = left.m_data[left.size() - i];
		result.rightShift(1);
		int count_div = 0;
		while (Money::compare(sub, right) != -1) {
			sub = sub - right;
			++count_div;
		}
		result.m_data[0] = count_div;
	}
	if (result.m_data[0] >= 5)
		result = result + Money("0,01").rightShift(1);
	result.leftShift(1);
	result.m_point_pos = 2;
	return result;
}