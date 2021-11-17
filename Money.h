#pragma once

#include "Array.h"
#include <sstream>
#include <regex>

using namespace std;

class Money : public Array {
public:
	Money();
	Money(const Money& money);
	Money(const string str);
	~Money();

	string toString() const;
	void fromString(string str);
	void removeLeadingZeros();
	virtual void print() const;

	virtual string tname() const { return "Money"; }

	static int compare(const Money& left, const Money& right);

	friend ostream& operator<<(ostream& out, const Money& right);
	friend istream& operator>>(istream& in, Money& right);
	friend bool operator==(const Money& left, const Money& right);

	friend Money operator*(const Money& left, const char right);
	virtual Money* operator+(const Money& right) const;
	virtual Money operator-(const Money& right) const;
	virtual Money operator*(const Money& right) const;
	virtual Money operator/(Money right) const;

	Money& rightShift(int right);
	Money& leftShift(int right);
	
	Money& operator=(const Money& right);

private:
	static const char m_base = 10;
	int m_point_pos = 2;

};

/*
Для всех:
Ввод
Вывод
Сложение



*/