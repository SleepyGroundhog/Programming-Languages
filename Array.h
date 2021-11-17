#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

void error(bool condition, int code, string msg);

class Array {
public:
	Array(int size = 0);
	Array(const Array& a);
	~Array();


	int size() const;
	static bool range(int value, int begin, int end);

	Array& operator=(const Array& right);
	char& operator[](int idx) const;


	friend ostream& operator<<(ostream& out, const Array& right);
	friend istream& operator>>(istream& in, const Array& right);

	virtual Array* operator+(const Array& right);

protected:
	int m_size;
	char* m_data;
	const static int MAX_SIZE = 10;
	void init();


};