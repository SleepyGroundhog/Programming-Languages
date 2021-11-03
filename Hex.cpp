#include "Hex.h"

Hex::Hex() : Array() {
	m_size = 1;
}

Hex::Hex(const Hex& a) {
	*this = a;
}

Hex::Hex(const string str) {
	newMemory();
	fromString(str);
}

Hex::~Hex() {}

int Hex::hexCharToInt(int hex_char) const {
	return (hex_char <= '9' ? (hex_char - '0') : (hex_char - 'A' + 10));
}

char Hex::intToHexChar(int int_value) const {
	return (int_value <= 9 ? (int_value + '0') : (int_value + 'A' - 10));
}

string Hex::toString() const {
	stringstream buf;
	for (int idx = getSize() - 1; idx >= 0; --idx) {
		buf << intToHexChar(m_data[idx]);
	}
	return buf.str();
}

void Hex::fromString(string str) { 
	resize((unsigned int)str.size());
	for (int idx = 0; idx < getSize(); ++idx) {
		at(idx) = hexCharToInt(str[str.size() - 1 - idx]);
	}
}

Hex& Hex::operator=(const Hex& a) {
	if (this != &a) {
		copy(a);  // Копирование полей класса Array
	}
	return *this;
}

ostream& operator<<(ostream& out, const Hex& a) {
	out << a.toString();
	return out;
}

istream& operator>>(istream& in, Hex& a) {
	string buf;
	in >> buf;
	a.fromString(buf);
	return in;
}

int Hex::compare(const Hex& a, const Hex& b) {
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

bool operator==(const Hex& a, const Hex& b) {
	return Hex::compare(a, b) == 0;
}

bool operator!=(const Hex& a, const Hex& b) {
	return Hex::compare(a, b) != 0;
}

bool operator>=(const Hex& a, const Hex& b) {
	return Hex::compare(a, b) != -1;
}

bool operator<=(const Hex& a, const Hex& b) {
	return Hex::compare(a, b) !=  1;
}

bool operator >(const Hex& a, const Hex& b) {
	return Hex::compare(a, b) ==  1;
}

bool operator <(const Hex& a, const Hex& b) {
	return Hex::compare(a, b) == -1;
}

// Сдвиг массива вправо (человеко-читаемое число сдвигается влево). Эквивалентно операции умножения на 10^x
Hex& Hex::rightShift(int x) {
	if (*this == Hex())
		return *this;
	for (int idx = getSize() - 1; idx >= 0; --idx)
		at(idx + x) = at(idx);
	for (int idx = 0; idx < x; ++idx)
		at(idx) = 0;
	m_size += x;
	return *this;
}

// Свиг массива влево (человеко-читаемое число сдвигается вправо)
Hex& Hex::leftShift(int x) {
	if (*this == Hex())
		return *this;
	for (int idx = 0; idx < getSize(); ++idx)
		at(idx) = at(idx + x);
	for (int idx = getSize() - x; idx < getSize(); ++idx)
		at(idx) = 0;
	m_size -= x;
	return *this;
}

void Hex::removeLeadingZeros() {
	while (at(getSize() - 1) == 0 && getSize() > 1)
		m_data[--m_size] = 0;;
}

Hex operator*(const Hex& a, const short hex_digit) {
	Hex c;
	assert(hex_digit >= 0 && hex_digit < 16 && "hex_digit is not hex digit");
	for (int idx = 0; idx < a.getSize(); ++idx) {
		c.at(idx) += (a.at(idx) * hex_digit);
		c.at(idx + 1) += c.at(idx) / Hex::m_base;
		c.at(idx) %= Hex::m_base;
	}
	c.m_size = (c.at(a.getSize()) == 0 ? a.getSize() : a.getSize() + 1); // Устанавливает размер результата учитывая изменение его размера
	c.removeLeadingZeros();
	return c;
}


Hex operator+(const Hex& a, const Hex& b) {
	Hex c;
	int max = std::max(a.m_size, b.m_size);
	for (int idx = 0; idx < max; ++idx) {
		c.at(idx) += a.at(idx) + b.at(idx);
		c.at(idx + 1) += c.at(idx) / Hex::m_base;
		c.at(idx) %= Hex::m_base;
	}
	if (c.at(Hex::MAX_SIZE) != 0)
		throw overflow_error("\nMoney.h : Money operator+(const Money& a, const Money& b) :\n\t\t\t money overflow\n");
	c.m_size = (c.at(max) == 0 ? max : max + 1);  // Устанавливает размер результата учитывая изменение его размера	
	return c;
}

Hex operator-(const Hex& a, const Hex& b) {
	Hex c;
	if (a < b) {
		cerr << "a < b, subtraction fail, return 0\n";
		return Hex(0);
	}
	for (int idx = 0; idx < a.getSize() + 1; ++idx) {
		c.at(idx) += a.at(idx) - b.at(idx);
		if (c.m_data[idx] < 0) {
			c.at(idx) += Hex::m_base;
			c.at(idx + 1) -= 1;
		}
	}
	c.m_size = a.getSize();
	c.removeLeadingZeros();
	return c;
}

Hex operator*(const Hex& a, const Hex& b) {
	Hex c;
	for (int idx = b.getSize() - 1; idx >= 0; --idx) {
		c.rightShift(1);
		c = c + (a * b.at(idx)); // при переполнении здесь сработает исключение для сложения
	}
	return c;
}

Hex operator/(const Hex& a, const Hex& b) {
	Hex result, sub;
	for (int i = 0; a.getSize() - i >= 0; ++i) {
		sub.rightShift(1);
		sub.at(0) = a.at(a.getSize() - i);
		result.rightShift(1);
		int count_div = 0;
		while (sub >= b) {
			sub = sub - b;
			++count_div;
		}
		result.at(0) = count_div;
	}
	return result;
}