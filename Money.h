#pragma once

#include "Array.h"
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <cassert>

using namespace std;

class Money : public Array<short int>
{
private:
	static const short m_base = 10;
	bool m_is_negative = false;
	// TODO �������� ��������� ������� �����
public:
	// ������ ��� ���������� ������������� ����������� ��������. ���������� ��� ��������� �.�. ����� �������� �� ���������
	// �������� �����
	static Money uIntAdd(const Money& a, const Money& b);
	static Money uIntSub(const Money& a, const Money& b);
	static Money uIntMulByDigit(const Money& a, const short digit);
	static Money uIntMul(const Money& a, const Money& b);
	static Money uIntDiv(const Money& a, const Money& b);

public:
	// ������������, ������������, ���������� ��������� ������������.
	Money();
	Money(const Money& a);
	Money(const string str);
	~Money();
	Money& operator=(const Money& a);

	// ������ ��������� ��������� ����� � ��������������.
	string toString() const;
	void fromString(string str);
	void removeLeadingZeros();

	bool isNegative() const;

	friend ostream& operator<<(ostream& out, const Money& a);
	friend istream& operator>>(istream& in, Money& a);

	
	// ������ � ��������� ���������
	static int compareByAbs(const Money& a, const Money& b);
	static int compare(const Money& a, const Money& b);

	friend bool operator==(const Money& a, const Money& b);
	friend bool operator!=(const Money& a, const Money& b);
	friend bool operator>=(const Money& a, const Money& b);
	friend bool operator<=(const Money& a, const Money& b);
	friend bool operator >(const Money& a, const Money& b);
	friend bool operator <(const Money& a, const Money& b);
	
	// �������� �������������� ���������

	Money& rightShift(int x);
	Money& leftShift(int x);

	friend Money operator+(const Money& a, const Money& b);
	friend Money operator-(const Money& a, const Money& b);

	Money operator+();
	Money operator-();

	//friend Money operator*(const Money& a, const Money& b);
	//friend Money operator*(const Money& a, const short digit);
	//friend Money operator/(Money a, const Money& b);	

};

