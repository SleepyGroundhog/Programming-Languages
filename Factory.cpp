//Factory.cpp
#include <iostream> 
#include "Factory.h" 
#include "Menu.h" 
#include "SymbString.h" 
#include "OctString.h" 
using namespace std;

void Factory::addObject() {
	std::cout << "\n�������� ��� �������:\n";
	std::cout << "1. ���������� ������ (SymbString)\n";
	std::cout << "2. ������������ ������ (OctString)\n\n";
	int code = UI::readCode(2);

	string name;  std::cout << "\n������� ������������� �������: ";  cin >> name;
	string value; std::cout << "������� �������� �������: ";       cin >> value;
	SymbString* pNewObj;
	switch (code) {
	case 1: pNewObj = new SymbString(name, value); break;
	case 2:
		if(!isOctStringValue(value)) { cout << "������: ��������� �������� �� �������� ������������ ������!\n\n"; return;
		}
		pNewObj = new OctString(name, value);
		break;
	}
	object.push_back(pNewObj);
	std::cout << "������ " << pNewObj->getId() << " ������.\n\n";
	cin.get();
}

void Factory::deleteObject() {
	int maxCode = (int)object.size();
	if (!maxCode) {
		cout << "\n��� ������������ ��������.\n\n";
		return;
	}

	cout << "�������� ������ ��� ��������:\n";
	for (int i = 0; i < maxCode; ++i)
		cout << i + 1 << ". " << object[i]->getId() << endl;
	int code = UI::readCode(maxCode);
	string objName = object[code - 1]->getId();
	object.erase(object.begin() + code - 1);
	cout << "������ " << objName << " ������.\n\n";
}

SymbString* Factory::selectObject() const {
	int maxCode = (int)object.size();
	if (!maxCode) {
		cout << "\n��� ������������ ��������.\n\n";
		return 0;
	}
	cout << "\n�������� ������:\n";
	for (int i = 0; i < maxCode; ++i) {
		cout << i + 1 << ". ";
		cout << object[i]->getId() << "\n";
	}
	cout << "\n";
	int code = UI::readCode(maxCode);
	return object[code - 1];
}


void Factory::print() {
	int maxCode = (int)object.size();
	if (!maxCode) {
		cout << "\n��� ������������ ��������.\n\n";
		return;
	}
	for (int i = 0; i < maxCode; ++i) {
		cout << i + 1 << ". " << object[i]->getId() << ": " << object[i]->getValue() << "\n";
	}
	cout << "\n";
}