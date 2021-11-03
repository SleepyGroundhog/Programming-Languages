#pragma once

#include "Array.h"

#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <cassert>


using namespace std;

class Hex : public Array<short int>
{
private:
	static const short m_base = 16;
	bool m_is_negative = false;

public:
	// Конструкторы, деструкторы, перегрузка оператора присваивания.
	Hex();
	Hex(const Hex& a);
	Hex(const string str);
	~Hex();
	Hex& operator=(const Hex& a);

	// Методы строковой обработки чисел и форматирования.
	string toString() const;
	void fromString(string str);
	void removeLeadingZeros();

	int hexCharToInt(int hex_char) const;
	char intToHexChar(int int_value) const;

	friend ostream& operator<<(ostream& out, const Hex& a);
	friend istream& operator>>(istream& in, Hex& a);

	
	// Методы и операторы сравнения
	static int compare(const Hex& a, const Hex& b);

	friend bool operator==(const Hex& a, const Hex& b);
	friend bool operator!=(const Hex& a, const Hex& b);
	friend bool operator>=(const Hex& a, const Hex& b);
	friend bool operator<=(const Hex& a, const Hex& b);
	friend bool operator >(const Hex& a, const Hex& b);
	friend bool operator <(const Hex& a, const Hex& b);
	
	// Основные арифметические операторы

	Hex& rightShift(int x);
	Hex& leftShift(int x);

	friend Hex operator+(const Hex& a, const Hex& b);
	friend Hex operator-(const Hex& a, const Hex& b);
	friend Hex operator*(const Hex& a, const Hex& b);
	friend Hex operator*(const Hex& a, const short digit);
	friend Hex operator/(const Hex& a, const Hex& b);
};

