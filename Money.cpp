#include "Money.h"

Money::Money() : Array() {
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
		buf << m_data[idx];
	return buf.str();
	// TODO Добавить учет знака и точки
}

void Money::fromString(string str) {
	if (regex_match(str.data(), regex(R"(\d{1,100})"))) { 
		resize(str.size());
		for (int idx = 0; idx < getSize(); ++idx)
			at(idx) = str[str.size() - 1 - idx] - '0';  // Перенос "перевёрнутой" строки в массив
	}
	else
		throw (invalid_argument("\nMoney.h : void fromString(string str) :\n\t\t\t string can't be converted to Money\n"));
	// TODO Добавить поддержку знаковых и дробных чисел
}

Money& Money::operator=(const Money& a) {
	if (this != &a) {
		copy(a);  // Копирование полей класса Array
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
	// TODO После добавления знака в число - изменить метод для работы со знаковыми числами
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

// Сдвиг массива вправо (человеко-читаемое число сдвигается влево). Эквивалентно операции умножения на 10^x
Money& Money::rightShift(int x) {
	assert(x > 0 && "x должен быть положительным. Для свига в другую сторону используется оператор leftShift(x)");
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
	assert(x > 0 && "x должен быть положительным. Для свига в другую сторону используется оператор rightShift(x)");
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

Money Money::uIntAddition(const Money& a, const Money& b) {
	Money c;
	int max = std::max(a.m_size, b.m_size);
	for (int idx = 0; idx < max; ++idx) {
		c.at(idx) += a.at(idx) + b.at(idx);
		c.at(idx + 1) += c.at(idx) / Money::m_base;
		c.at(idx) %= Money::m_base;
	}
	if (c.at(Money::MAX_SIZE) != 0)
		throw overflow_error("\nMoney.h : Money operator+(const Money& a, const Money& b) :\n\t\t\t money overflow\n");
	c.m_size = (c.at(max) == 0 ? max : max + 1);  // Устанавливает размер результата учитывая изменение его размера	
	return c;

}

Money Money::uIntSubtraction(const Money& a, const Money& b) {
	Money c;
	assert(a >= b && "Беззнаковое вычитание! a должно быть больше или равно b");
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

Money Money::uIntMultiplicationByDigit(const Money& a, const short digit) {
	Money c;
	assert(digit >= 0 && digit < 10 && "digit должна быть цифрой!");
	for (int idx = 0; idx < a.getSize(); ++idx) {
		c.at(idx) += (a.at(idx) * digit);
		c.at(idx + 1) += c.at(idx) / Money::m_base;
		c.at(idx) %= Money::m_base;
	}
	c.m_size = (c.at(a.getSize()) == 0 ? a.getSize() : a.getSize() + 1); // Устанавливает размер результата учитывая изменение его размера
	c.removeLeadingZeros();
	return c;
}

Money Money::uIntMultiplication(const Money& a, const Money& b) {
	Money c;
	if (b != Money()) {
		for (int idx = b.getSize() - 1; idx >= 0; --idx) {
			c.rightShift(1);
			c = c + Money::uIntMultiplicationByDigit(a, b.at(idx));
		}
	}
	return c;
}


// Метод целочисленного деления вычитанием. В связи с тем, что такое деление критично (видно невооруженным взгядом) медленное при b в ~100 раз меньшем, чем а
// то данная функция может использоваться только как вспомогательная для реализации более эффективных методов деления.
// Требование к входным данным: a < 10*b. При невыполнении данного условия функция будет работат слишком медленно, поэтому передача иных входных данных 
// будет вызывать ошибку.
short Money::div(Money& a, const Money& b) {
	short result = 0;
	assert(a < Money(b).rightShift(1) && "Требование к входным данным функции div: a < 10*b");
	while (a >= b) {
		a = a - b;
		++result;
	}
	return result;
}

Money Money::uIntDivision(const Money& a, const Money& b) {
	Money result, sub;
	for (int i = 0; a.getSize() - i >= 0; ++i) {
		sub.rightShift(1);
		sub.at(0) = a.at(a.getSize() - i);
		result.rightShift(1);
		result.at(0) = Money::div(sub, b);
	}
	return result;
}


Money operator+(const Money& a, const Money& b) {
	// TODO Доопределить до знаковых операций
	return Money::uIntAddition(a, b);
}
Money operator-(const Money& a, const Money& b) {
	// TODO Доопределить до знаковых операций
	return Money::uIntSubtraction(a, b);

}
