#include "Money.h"

Money::Money() : Array(), m_is_negative(false) {
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
	if (isNegative()) buf << "-";
	for (int idx = getSize() - 1; idx >= 0; --idx)
		buf << m_data[idx];
	return buf.str();
	// TODO ƒобавить учет знака и точки
}

void Money::fromString(string str) {
	if (regex_match(str.data(), regex(R"([+,-]?\d{1,100})"))) { 
		if (str[0] == '-' || str[0] == '+') {
			m_is_negative = (str[0] == '-');
			str.erase(0, 1);
		}
			
		resize((unsigned int)str.size());
		for (int idx = 0; idx < getSize(); ++idx)
			at(idx) = str[str.size() - 1 - idx] - '0';  // ѕеренос "перевЄрнутой" строки в массив
	}
	else
		throw (invalid_argument("\nMoney.h : void fromString(string str) :\n\t\t\t string can't be converted to Money\n"));
	// TODO ƒобавить поддержку дробных чисел
}

Money& Money::operator=(const Money& a) {
	if (this != &a) {
		copy(a);  //  опирование полей класса Array
		m_is_negative = a.isNegative();
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

int Money::compareByAbs(const Money& a, const Money& b) {
		if (a.m_size != b.m_size) // сравнение чисел по их длине
			return (a.m_size > b.m_size) ? 1 : -1;
		for (int idx = a.m_size - 1; idx >= 0; --idx) { // сравнение если числа одинаковой длинны
			if (a[idx] > b[idx])
				return 1;
			else if (a[idx] < b[idx])
				return -1;
		}
		return 0;
}

int Money::compare(const Money& a, const Money& b) {
	return compareByAbs(a, b);
	// TODO ѕосле добавлени€ знака в число - изменить метод дл€ работы со знаковыми числами
}

bool operator==(const Money& a, const Money& b) {
	return Money::compare(a, b) == 0;
}

bool operator!=(const Money& a, const Money& b) {
	return Money::compare(a, b) != 0;
}

bool operator>=(const Money& a, const Money& b) {
	return Money::compare(a, b) != -1;
}

bool operator<=(const Money& a, const Money& b) {
	return Money::compare(a, b) !=  1;
}

bool operator >(const Money& a, const Money& b) {
	return Money::compare(a, b) ==  1;
}

bool operator <(const Money& a, const Money& b) {
	return Money::compare(a, b) == -1;
}

// —двиг массива вправо (человеко-читаемое число сдвигаетс€ влево). Ёквивалентно операции умножени€ на 10^x
Money& Money::rightShift(int x) {
	assert(x > 0 && "x должен быть положительным. ƒл€ свига в другую сторону используетс€ оператор leftShift(x)");
	if (*this == Money())
		return *this;
	for (int idx = getSize() - 1; idx >= 0; --idx)
		at(idx + x) = at(idx);
	for (int idx = 0; idx < x; ++idx)
		at(idx) = 0;
	m_size += x;
	return *this;
}

// —виг массива влево (человеко-читаемое число сдвигаетс€ вправо)
Money& Money::leftShift(int x) {
	assert(x > 0 && "x должен быть положительным. ƒл€ свига в другую сторону используетс€ оператор rightShift(x)");
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
}

Money Money::uIntAdd(const Money& a, const Money& b) {
	Money c;
	int max = (a.m_size >= b.m_size ? a.m_size : b.m_size);
	for (int idx = 0; idx < max; ++idx) {
		c.at(idx) += a.at(idx) + b.at(idx);
		c.at(idx + 1) += c.at(idx) / Money::m_base;
		c.at(idx) %= Money::m_base;
	}
	if (c.at(Money::MAX_SIZE) != 0)
		throw overflow_error("\nMoney.h : Money operator+(const Money& a, const Money& b) :\n\t\t\t money overflow\n");
	c.m_size = (c.at(max) == 0 ? max : max + 1);  // ”станавливает размер результата учитыва€ изменение его размера	
	return c;

}

Money Money::uIntSub(const Money& a, const Money& b) {
	Money c;
	assert(a >= b && "unsigned subtraction - a have to be greater or equal b");
	for (int idx = 0; idx < a.getSize() + 1; ++idx) {
		c.at(idx) += a.at(idx) - b.at(idx);
		if (c.m_data[idx] < 0) {
			c.at(idx) += Money::m_base;
			c.at(idx + 1) -= 1;
		}
	}
	c.m_size = a.getSize();	
	c.removeLeadingZeros();
	return c;
}

Money Money::uIntMulByDigit(const Money& a, const short digit) {
	Money c;
	assert(digit >= 0 && digit < 10 && "digit is not digit");
	for (int idx = 0; idx < a.getSize(); ++idx) {
		c.at(idx) += (a.at(idx) * digit);
		c.at(idx + 1) += c.at(idx) / Money::m_base;
		c.at(idx) %= Money::m_base;
	}
	c.m_size = (c.at(a.getSize()) == 0 ? a.getSize() : a.getSize() + 1); // ”станавливает размер результата учитыва€ изменение его размера
	c.removeLeadingZeros();
	return c;
}

Money Money::uIntMul(const Money& a, const Money& b) {
	Money c;
	for (int idx = b.getSize() - 1; idx >= 0; --idx) {
		c.rightShift(1);
		c = uIntAdd(c, Money::uIntMulByDigit(a, b.at(idx))); // при переполнении сдесь сработает исключение дл€ сложени€
	}
	return c;
}

Money Money::uIntDiv(const Money& a, const Money& b) {
	Money result, sub;
	for (int i = 0; a.getSize() - i >= 0; ++i) {
		sub.rightShift(1);
		sub.at(0) = a.at(a.getSize() - i);
		result.rightShift(1);
		int count_div = 0;
		while (sub >= b) {
			sub = uIntSub(sub, b);
			++count_div;
		}
		result.at(0) = count_div;
	}
	return result;
}

Money operator+(const Money& a, const Money& b) {
	// TODO ƒоопределить до знаковых операций
	return Money::uIntAdd(a, b);
}

Money operator-(const Money& a, const Money& b) {
	// TODO ƒоопределить до знаковых операций
	return Money::uIntSub(a, b);

}



bool Money::isNegative() const {
	return m_is_negative;
}

Money Money::operator+() {
	return *this;
}

Money Money::operator-() {
	Money temp(*this);
	temp.m_is_negative = !temp.isNegative();
	return temp;
}