#pragma once

#include "Array.h"
#include <sstream>
#include <regex>

class Money : public Array {
public:
	Money();
	Money(const Money& money);
	Money(const std::string str);
	~Money();

	virtual Money& operator=(const Money& right);

	virtual std::string toString() const;
	void fromString(std::string str);

	void removeLeadingZeros();
	static int compare(const Money& left, const Money& right);

	friend std::istream& operator>>(std::istream& in, Money& right);
	friend bool operator==(const Money& left, const Money& right);

	friend Money operator*(const Money& left, const char right);
	virtual Money operator+(const Money& right) const;
	virtual Money operator-(const Money& right) const;
	virtual Money operator*(const Money& right) const;
	virtual Money operator/(Money right) const;

	Money& rightShift(int right);
	Money& leftShift(int right);

private:
	static const char m_base = 10;
	int m_point_pos = 2;

};