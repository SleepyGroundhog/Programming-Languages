// Action.cpp
#include <iostream>
#include "Action.h" 
#include "HexString.h"
using namespace std;

#pragma warning(disable : 4996)

int HexToInt(char hexDigit) {
	if (hexDigit >= '0' && hexDigit <= '9')
		return hexDigit - '0';
	if (hexDigit >= 'A' && hexDigit <= 'F')
		return hexDigit - 'A' + 10;
}

long Action::GetDecimal(AString* pObj) const {
	if (dynamic_cast<HexString*>(pObj)) {
		long dest = 0;
		string source = pObj->GetVal();
		for (int i = 0; i < source.size(); ++i) {
			dest += HexToInt(source[i] * pow(16, source.size() - 1 - i));
		}
		return dest;
	}
	else {
		cout << "Action not supported." << endl;
		return -1;
	}
}