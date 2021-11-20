// ShowDec.cpp 
#include <iostream> 
#include "ShowDec.h" 
#include "HexString.h" 
using namespace std;

void ShowDec::Operate(AString* pObj) {
	cout << pObj->GetName() << ": ";
	long decVal = GetDecimal(pObj);
	if (decVal != -1)
		cout << GetDecimal(pObj);
	cout << endl;
	cin.get();
}

ShowDec show_dec; // Глобальный объект 