// ShowDec.cpp 
#include <iostream> 
#include "ShowDec.h" 
#include "OctString.h" 
using namespace std;

void ShowDec::operate(SymbString* object) {
	cout << object->getName() << ": ";
	long decVal = GetDecimal(object);
	if (decVal != -1)
		cout << GetDecimal(object);
	cout << endl;
}

ShowDec show_dec; // Глобальный объект 