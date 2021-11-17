#pragma once

#include "Array.h"

class BitString : Array {
public:
	BitString(int size = 0);


	friend ostream& operator<<(ostream& output, const BitString& right);
	friend istream& operator>>(istream& input, BitString& right);
	friend BitString operator~(BitString right);
	friend BitString operator&(BitString left, const BitString& right);
	friend BitString operator|(BitString left, const BitString& right);
	friend BitString operator^(BitString left, const BitString& right);
	BitString& operator>>(int x);
	BitString& operator<<(int x);
	BitString& operator=(const BitString& right);
	virtual Array* operator+(const Array& right);

};