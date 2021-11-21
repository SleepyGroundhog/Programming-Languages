// HexStrIng.cpp 
#include <iostream>
#include "OctString.h"
using namespace std;

bool isOctStringValue(string str) {
	static const std::string octAlphabet = "012345678";
	for (int i = 0; i < str.size(); ++i)
		if (-1 == octAlphabet.find_first_of(str[i])) return false;
	return true;
}
	
OctString::OctString(string name, string value) : SymbString(name) {
	if(isOctStringValue(value))
		m_value = value;
}

SymbString* OctString::operator+(SymbString object2) {
	if (!isOctStringValue(getValue()) || !isOctStringValue(object2.getValue()))
		return (SymbString)(*this) + (SymbString)object2;

	string right = getValue(), left = object2.getValue();
	reverse(right.begin(), right.end()), reverse(left.begin(), left.end()), right.append("0"), left.append(string(right.size() - left.size(), '0'));
	for (int i = 0; i < left.size(); i++) {
		right[i] += left[i] - '0';
		right[i + 1] += ((int)((right[i] - '0') / 8));
		right[i] = (int)(right[i] - '0') % 8 + '0';
	}
	if (right[right.size() - 1] == '0')
		right.pop_back();
	reverse(right.begin(), right.end()), reverse(left.begin(), left.end());
	OctString* result = new OctString(getId() + " + " + object2.getId(), right);
	return result;
}