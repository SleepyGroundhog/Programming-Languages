#pragma once

#include "Array.h"

class BitString : Array {
public:
	BitString(int size = 0);
	BitString(string str);

	void fromString(string str);
	virtual void print() const;

	friend ostream& operator<<(ostream& out, const BitString& right);
	friend istream& operator>>(istream& in, BitString& right);

	virtual BitString& operator>>(int right);
	virtual BitString& operator<<(int right);
	virtual BitString& operator=(const BitString& right);
	virtual BitString operator&(const BitString& right);
	virtual BitString operator+(const BitString& right);
	virtual BitString operator~();
	virtual BitString operator^(const BitString& right);

	virtual string tname() const { return "BitString"; }
};