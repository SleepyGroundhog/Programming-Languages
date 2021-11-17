#include "Money.h"

Money Money::uIntAdd(const Money& left, const Money& right) {
	Money result;
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

Money Money::uIntSub(const Money& left, const Money& right) {
	Money result;
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

Money Money::uIntMulByDigit(const Money& left, const char right) {
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

Money Money::uIntMul(const Money& left, const Money& right) {
	Money result;
	for (int idx = right.size() - 1; idx >= 0; --idx) {
		result.rightShift(1);
		result = uIntAdd(result, Money::uIntMulByDigit(left, right.m_data[idx]));
	}
	return result;
}

Money Money::uIntDiv(const Money& left, const Money& right) {
	error(right == Money(), 3, "division by zero");
	Money result, sub;
	for (int i = 0; left.size() - i >= 0; ++i) {
		sub.rightShift(1);
		sub.m_data[0] = left.m_data[left.size() - i];
		result.rightShift(1);
		int count_div = 0;
		while (compareByAbs(sub, right ) != -1) {
			sub = uIntSub(sub, right);
			++count_div;
		}
		result.m_data[0] = count_div;
	}
	return result;
}

Money::Money() : Array(), m_is_negative(false), m_point_pos(2) { m_size = 1; }
Money::Money(const Money& a) { *this = a; }
Money::Money(const string str) : Array() { fromString(str); }
Money::~Money() {}

Money& Money::operator=(const Money& a) {
	if (this != &a) {
		if (a.size() < m_size)
			for (int idx = a.size(); idx < m_size; ++idx)
				m_data[idx] = 0;
		m_size = a.size();
		for (int idx = 0; idx < size(); ++idx)
			m_data[idx] = a[idx];
		m_is_negative = a.isNegative();
		m_point_pos = a.m_point_pos;
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
	if (isNegative()) result.insert(0, "-");
	return result;
}

void Money::fromString(string str) {
	if (str == "0") { *this = Money(); return; }
	error(!regex_match(str.data(), regex(R"([+,-]?\d{1,100},\d{2})")), 3, "string can't be converted to Money");
	if (str[0] == '-' || str[0] == '+') {
		m_is_negative = (str[0] == '-');
		str.erase(0, 1);
	}
	str.erase(str.size() - 3, 1);
	if ((int)str.size() < m_size)
		for (int idx = str.size(); idx < m_size; ++idx)
			m_data[idx] = 0;
	m_size = str.size();
	for (int idx = 0; idx < size(); ++idx)
		m_data[idx] = str[str.size() - 1 - idx] - '0';  // Перенос "перевёрнутой" строки в массив
}

void Money::removeLeadingZeros() {
	while (m_data[size() - 1] == 0 && size() > 1)
		m_data[--m_size] = 0;
	if (size() == 1 && m_data[0] == 0)
		m_is_negative = false;
}

bool Money::isNegative() const { return m_is_negative; }

ostream& operator<<(ostream& out, const Money& a) { out << a.toString(); return out; }

istream& operator>>(istream& in, Money& a) {
	string buf;
	in >> buf;
	a.fromString(buf);
	return in;
}

int Money::compareByAbs(const Money& left, const Money& right) {
	for (int idx = max(left.size(), right.size()) - 1; idx >= 0; --idx)
		if (left.m_data[idx] > right.m_data[idx])
			return 1;
		else if (left.m_data[idx] < right.m_data[idx])
			return -1;
	return 0;
}

int Money::compare(const Money& left, const Money& right) {
	if (left.isNegative() != right.isNegative())  return  right.isNegative() ? 1 : -1;
	if (!left.isNegative())						  return  Money::compareByAbs(left, right);
	else										  return -Money::compareByAbs(left, right);
}

bool operator==(const Money& left, const Money& right) { return Money::compare(left, right) == 0; }
bool operator!=(const Money& left, const Money& right) { return Money::compare(left, right) != 0; }
bool operator>=(const Money& left, const Money& right) { return Money::compare(left, right) != -1; }
bool operator<=(const Money& left, const Money& right) { return Money::compare(left, right) != 1; }
bool operator >(const Money& left, const Money& right) { return Money::compare(left, right) == 1; }
bool operator <(const Money& left, const Money& right) { return Money::compare(left, right) == -1; }

Money& Money::rightShift(int x) {
	if (*this == Money())
		return *this;
	for (int idx = size() - 1; idx >= 0; --idx)
		m_data[idx + x] = m_data[idx];
	for (int idx = 0; idx < x; ++idx)
		m_data[idx] = 0;
	m_size += x;
	return *this;
}

Money& Money::leftShift(int x) {
	if (*this == Money())
		return *this;
	for (int idx = 0; idx < size(); ++idx)
		m_data[idx] = m_data[idx + x];
	for (int idx = size() - x; idx < size(); ++idx)
		m_data[idx] = 0;
	m_size -= x;
	return *this;
}

Money Money::operator+() const { return *this; }

Money Money::operator-() const {
	Money temp(*this);
	temp.m_is_negative = !temp.isNegative();
	return temp;
}

Money operator+(const Money& left, const Money& right) {
	if (left.isNegative()) {
		if (right.isNegative()) return -(-left + (-right));
		else return right - (-left);
	}
	else if (right.isNegative())
		return right - (-left);
	return Money::uIntAdd(right, left);
}

Money operator-(const Money& left, const Money& right) {
	if (right.isNegative()) return left + (-right);
	else if (left.isNegative()) return -(-left + right);
	else if (left < right) return -(right - left);
	return Money::uIntSub(left, right);
}

Money operator*(const Money& left, const Money& right) {
	Money result = (left.isNegative() == right.isNegative() ? Money::uIntMul(left, right) : -Money::uIntMul(left, right));
	if (result.size() == 1 && result.m_data[0] == 0) result.m_is_negative = false;
	if (result.m_data[1] >= 5)
		result = result + Money("0,01").rightShift(2);
	result.leftShift(2);
	result.m_point_pos = 2;
	return result;
}

Money operator/(Money left, Money right) {
	Money result;
	error(right == Money() || right == Money("0,00"), 3, "division by zero");
	if (Money::compareByAbs(left.rightShift(5), right.rightShift(2)) == -1) {
		return result;
	}
	result = (left.isNegative() == right.isNegative() ? Money::uIntDiv(left, right) : -Money::uIntDiv(left, right));
	if (result.size() == 1 && result.m_data[0] == 0) result.m_is_negative = false;
	if (result.m_data[0] >= 5)
		result = result + Money("0,01").rightShift(1);
	result.leftShift(1);
	result.m_point_pos = 2;
	return result;
}

/*
Array* Array::sum(const Array& right) {
	Array* result;
	result = new Array(max(size(), right.size()));
	for (int i = 0; i < result->size(); ++i)
		result->m_data[i] = m_data[i] + right.m_data[i];
	return result;
}

*/