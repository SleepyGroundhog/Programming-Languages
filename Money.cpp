#include "Money.h"

Money::Money() : Array(), m_is_negative(false), m_point_pos(2) {
	m_size = 1;
}

Money::Money(const Money& a) {
	*this = a;
}

Money::Money(const string str) {
	newMemory();
	fromString(str);
}

Money::~Money() {}

string Money::toString() const {
	stringstream buf;
	for (int idx = getSize() - 1; idx >= 0; --idx)
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
	if (regex_match(str.data(), regex(R"([+,-]?\d{1,100},\d{2})"))) { 
		if (str[0] == '-' || str[0] == '+') {
			m_is_negative = (str[0] == '-');
			str.erase(0, 1);
		}
		str.erase(str.size() - 3, 1);
		resize((unsigned int)str.size());
		for (int idx = 0; idx < getSize(); ++idx)
			at(idx) = str[str.size() - 1 - idx] - '0';  // Перенос "перевёрнутой" строки в массив
	}
	else
		throw (invalid_argument("\nMoney.h : void fromString(string str) :\n\t\t\t string can't be converted to Money\n"));
	// TODO Добавить поддержку дробных чисел
}

Money& Money::operator=(const Money& a) {
	if (this != &a) {
		copy(a);  // Копирование полей класса Array
		m_is_negative = a.isNegative();
		m_point_pos = a.m_point_pos;
	}
	return *this;
}

ostream& operator<<(ostream& out, const Money& a) {
	out << a.toString();
	return out;
}

istream& operator>>(istream& in, Money& a) {
	string buf;
	in >> buf;
	a.fromString(buf);
	return in;
}

int Money::compareByAbs(const Money& left, const Money& right) {
		if (left.getSize() != right.getSize()) // сравнение чисел по их длине
			return (left.getSize() > right.getSize()) ? 1 : -1;
		for (int idx = left.getSize() - 1; idx >= 0; --idx) { // сравнение если числа одинаковой длинны
			if (left[idx] > right[idx])
				return 1;
			else if (left[idx] < right[idx])
				return -1;
		}
		return 0;
}

int Money::compare(const Money& left, const Money& right) {
	if (left.isNegative() != right.isNegative())
		return right.isNegative() ? 1 : -1;
	if (!left.isNegative()) {
		return Money::compareByAbs(left, right);
	}
	else {
		return -Money::compareByAbs(left, right);
	}
}

bool operator==(const Money& left, const Money& right) {
	return Money::compare(left, right) == 0;
}

bool operator!=(const Money& left, const Money& right) {
	return Money::compare(left, right) != 0;
}

bool operator>=(const Money& left, const Money& right) {
	return Money::compare(left, right) != -1;
}

bool operator<=(const Money& left, const Money& right) {
	return Money::compare(left, right) !=  1;
}

bool operator >(const Money& left, const Money& right) {
	return Money::compare(left, right) ==  1;
}

bool operator <(const Money& left, const Money& right) {
	return Money::compare(left, right) == -1;
}

// Сдвиг массива вправо (человеко-читаемое число сдвигается влево). Эквивалентно операции умножения на 10^x
Money& Money::rightShift(int x) {
	if (*this == Money())
		return *this;
	for (int idx = getSize() - 1; idx >= 0; --idx)
		at(idx + x) = at(idx);
	for (int idx = 0; idx < x; ++idx)
		at(idx) = 0;
	m_size += x;
	return *this;
}

// Свиг массива влево (человеко-читаемое число сдвигается вправо)
Money& Money::leftShift(int x) {
	if (*this == Money())
		return *this;
	for (int idx = 0; idx < getSize(); ++idx)
		at(idx) = at(idx + x);
	for (int idx = getSize() - x; idx < getSize(); ++idx)
		at(idx) = 0;
	m_size -= x;
	return *this;
}

void Money::removeLeadingZeros() {
	while (at(getSize() - 1) == 0 && getSize() > 1)
		pop();
	if (getSize() == 1 && at(0) == 0)
		m_is_negative = false;
}

Money Money::uIntAdd(const Money& left, const Money& right) {
	Money result;
	int max = (left.m_size >= right.m_size ? left.m_size : right.m_size);
	for (int idx = 0; idx < max; ++idx) {
		result.at(idx) += left.at(idx) + right.at(idx);
		result.at(idx + 1) += result.at(idx) / Money::m_base;
		result.at(idx) %= Money::m_base;
	}
	if (result.at(Money::MAX_SIZE) != 0)
		throw overflow_error("\nMoney.h : Money operator+(const Money& a, const Money& b) :\n\t\t\t money overflow\n");
	result.m_size = (result.at(max) == 0 ? max : max + 1);  // Устанавливает размер результата учитывая изменение его размера	
	return result;

}

Money Money::uIntSub(const Money& left, const Money& right) {
	Money result;
	for (int idx = 0; idx < left.getSize() + 1; ++idx) {
		result.at(idx) += left.at(idx) - right.at(idx);
		if (result.m_data[idx] < 0) {
			result.at(idx) += Money::m_base;
			result.at(idx + 1) -= 1;
		}
	}
	result.m_size = left.getSize();	
	result.removeLeadingZeros();
	return result;
}

Money Money::uIntMulByDigit(const Money& left, const char right_digit) {
	Money result;
	for (int idx = 0; idx < left.getSize(); ++idx) {
		result.at(idx) += (left.at(idx) * right_digit);
		result.at(idx + 1) += result.at(idx) / Money::m_base;
		result.at(idx) %= Money::m_base;
	}
	result.m_size = (result.at(left.getSize()) == 0 ? left.getSize() : left.getSize() + 1); // Устанавливает размер результата учитывая изменение его размера
	result.removeLeadingZeros();
	return result;
}

Money Money::uIntMul(const Money& left, const Money& right) {
	Money result;
	for (int idx = right.getSize() - 1; idx >= 0; --idx) {
		result.rightShift(1);
		result = uIntAdd(result, Money::uIntMulByDigit(left, right.at(idx))); // при переполнении сдесь сработает исключение для сложения
	}
	return result;
}

Money Money::uIntDiv(const Money& left, const Money& right) {
	if (right == Money())
		throw exception("\nMoney.cpp : Money uIntDiv(const Money& left, const Money& right) :\n\t\t\t division by zero\n");
	Money result, sub;
	for (int i = 0; left.getSize() - i >= 0; ++i) {
		sub.rightShift(1);
		sub.at(0) = left.at(left.getSize() - i);
		result.rightShift(1);
		int count_div = 0;
		while (compareByAbs(sub, right) != -1) {
			sub = uIntSub(sub, right);
			++count_div;
		}
		result.at(0) = count_div;
	}
	return result;
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

bool Money::isNegative() const {
	return m_is_negative;
}

Money Money::operator+() const {
	return *this;
}

Money Money::operator-() const {
	Money temp(*this);
	temp.m_is_negative = !temp.isNegative();
	return temp;
}


Money operator*(const Money& left, const Money& right) {
	Money result = (left.isNegative() == right.isNegative() ? Money::uIntMul(left, right) : -Money::uIntMul(left, right));
	if (result.getSize() == 1 && result.at(0) == 0) result.m_is_negative = false;
	if (result.at(1) >= 5)
		result = result + Money("0,01").rightShift(2);
	result.leftShift(2);
	result.m_point_pos = 2;
	return result;
}


Money operator/(Money left, Money right) {
	Money result;	
	if (right == Money() || right == Money("0,00"))
		throw exception("division by zero");
	if (Money::compareByAbs(left.rightShift(5), right.rightShift(2)) == -1) {
		return result;
	}
	result = (left.isNegative() == right.isNegative() ? Money::uIntDiv(left, right) : -Money::uIntDiv(left, right));
	if (result.getSize() == 1 && result.at(0) == 0) result.m_is_negative = false;
	if (result.at(0) >= 5)
		result = result + Money("0,01").rightShift(1);
	result.leftShift(1);
	result.m_point_pos = 2;
	return result;
}