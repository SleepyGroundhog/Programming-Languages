#pragma once

#include "Array.h"
#include <sstream>
#include <regex>

using namespace std;

class Money : public Array {
public:
	Money();
	Money(const Money& a);
	Money(const string str);
	~Money();

	string toString() const;
	void fromString(string str);
	void removeLeadingZeros();
	bool isNegative() const;


	static int compareByAbs(const Money& left, const Money& right);
	static int compare(const Money& left, const Money& right);


	friend ostream& operator<<(ostream& out, const Money& a);
	friend istream& operator>>(istream& in, Money& a);
	friend bool operator==(const Money& left, const Money& right);
	friend bool operator!=(const Money& left, const Money& right);
	friend bool operator>=(const Money& left, const Money& right);
	friend bool operator<=(const Money& left, const Money& right);
	friend bool operator >(const Money& left, const Money& right);
	friend bool operator <(const Money& left, const Money& right);
	friend Money operator+(const Money& left, const Money& right);
	friend Money operator-(const Money& left, const Money& right);
	friend Money operator*(const Money& left, const Money& right);
	friend Money operator/(Money left, Money right);


	Money& rightShift(int x);
	Money& leftShift(int x);


	Money operator+() const;
	Money operator-() const;
	Money& operator=(const Money& a);
	
	static Money uIntAdd(const Money& left, const Money& right);
	static Money uIntSub(const Money& left, const Money& right);
	static Money uIntMul(const Money& left, const Money& right);
	static Money uIntDiv(const Money& left, const Money& right);
	static Money uIntMulByDigit(const Money& left, const char right);

	Array* sum(const Array& right);

private:
	static const char m_base = 10;
	bool m_is_negative = false;
	int m_point_pos = 2;


};