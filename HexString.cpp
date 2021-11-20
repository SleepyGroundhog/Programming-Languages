// HexStrIng.cpp 
#include <iostream>
#include "HexString.h"
using namespace std;

bool IsHexStrVal(string _str) {
	for (int i = 0; i < _str.size(); ++i)
		if (-1 == alph.find_first_of(_str[i])) return false;
	return true;
}
	
HexString::HexString(string _name, string _val) :
	name (_name) {
	if(IsHexStrVal(_val))
		val = _val;
}