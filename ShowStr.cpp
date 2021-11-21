// ShowStr.cpp 
#include <iostream> 
#include "ShowStr.h" 
using namespace std;

void ShowString::operate(SymbString* object) {
	cout << object->getName() << ": ";
	cout << object->getValue() << endl;
}

void ShowString::operator()(SymbString* object) {
	cout << object->getName() << ": ";
	cout << object->getValue() << endl;
}

ShowString show_str; // Глобальный объект