// Action.cpp
#include <iostream>
#include "Action.h" 
#include "OctString.h"
using namespace std;

int OctToInt(char octDigit) {
	if (octDigit >= '0' && octDigit < '8')
		return octDigit - '0';
}

long Action::GetDecimal(SymbString* object) const {
	if (dynamic_cast<OctString*>(object)) {
		long dest = 0;
		string source = object->getValue();
		for (int i = 0; i < source.size(); ++i) {
			dest += source[i] - '0' * pow(8, source.size() - 1 - i);
		}
		return dest;
	}
	else {
		cout << "Операция не поддерживается." << endl;
		return -1;
	}
}