// HexStrIng.cpp 
#include <iostream>
#include "OctString.h"
using namespace std;

bool isOctStringValue(string _str) {
	static const std::string octAlphabet = "012345678";
	for (int i = 0; i < _str.size(); ++i)
		if (-1 == octAlphabet.find_first_of(_str[i])) return false;
	return true;
}
	
OctString::OctString(string _name, string _val) :
	m_name (_name) {
	if(isOctStringValue(_val))
		m_value = _val;
}