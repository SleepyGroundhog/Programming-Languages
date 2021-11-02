#pragma once

#include "Array.h"

#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <cassert>
#include <algorithm>


using namespace std;

class Money : public Array<short int>
{
private:
	static const short m_base = 10;
	// TODO �������� ����
	// TODO �������� ��������� ������� �����
public:
	// ������ ��� ���������� ������������� ����������� ��������. ���������� ��� ��������� �.�. ����� �������� �� ���������
	// �������� �����
	static Money uIntAddition(const Money& a, const Money& b);
	static Money uIntSubtraction(const Money& a, const Money& b);
	static Money uIntMultiplicationByDigit(const Money& a, const short digit);
	static Money uIntMultiplication(const Money& a, const Money& b);
	static short div(Money& a, const Money& b);
	static Money uIntDivision(const Money& a, const Money& b);

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

	

	

	//
	//
	//friend Money operator*(const Money& a, const Money& b);
	//friend Money operator*(const Money& a, const short digit);
	//friend Money operator/(Money a, const Money& b);


	

};

