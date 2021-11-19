#pragma once

#include "Array.h"

class BitString : public Array {
public:
	BitString(int size = 0);
	BitString(std::string str);
	BitString(const BitString& bstr);
	~BitString();

	virtual BitString& operator=(const BitString& right);

	virtual std::string toString() const;
	void fromString(std::string str);

	virtual BitString& operator>>(int right);
	virtual BitString& operator<<(int right);
	virtual BitString operator^(BitString right) const;
	virtual BitString operator&(BitString right) const;
	virtual BitString operator+(BitString right) const;
	virtual BitString operator~() const;
	
	friend std::istream& operator>>(std::istream& in, BitString& right);
};