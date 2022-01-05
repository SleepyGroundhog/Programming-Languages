#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

void error(bool condition, int code, std::string msg);



class Array {
public:
	Array(int size = 0);
	Array(const Array& a);
	~Array();

	virtual Array& operator=(const Array& right);

	virtual std::string toString() const;
	int size() const;
	static bool range(int value, int begin, int end);

	friend std::istream& operator>>(std::istream& in, const Array& right);
	int& operator[](int idx) const;
	
	virtual Array operator+(const Array& right) const;

protected:
	int m_size;
	int* m_data;
	const static int MAX_SIZE = 50;
	void init();

};

std::ostream& operator<<(std::ostream& out, const Array& right);