#include <iostream> 
#include "Factory.h" 
#include "UI.h" 
#include "SymbString.h" 
#include "OctString.h" 
using namespace std;

void Factory::addObject() {
	std::cout << "\n�������� ��� �������:\n";
	std::cout << "1. ���������� ������\n";
	std::cout << "2. ������������ ������\n\n";
	int code = UI::readCode(2);

	string id;    std::cout << "\n������� ������������� �������: ";  cin >> id;
	string value; std::cout << "������� �������� �������: ";         cin >> value;
	SymbString* newObject;
	switch (code) {
	case 1: newObject = new SymbString(id, value); break;
	case 2:
		if (!isOctStringValue(value)) {
			cout << "\n������: ��������� �������� �� �������� ������������ ������!\n\n"; cin.get(); return;
		}
		newObject = new OctString(id, value);
		break;
	}
	m_object.push_back(newObject);
	std::cout << "\n������ " << newObject->getId() << " ������.\n\n";
	cin.get();
}

void Factory::deleteObject() {
	int maxCode = (int)m_object.size();
	if (!maxCode) {
		cout << "\n��� ������������ ��������.\n\n";
		return;
	}

	cout << "\n�������� ������ ��� ��������:\n";
	for (int i = 0; i < maxCode; ++i)
		cout << i + 1 << ". " << m_object[i]->getId() << endl;
	cout << "\n";
	int code = UI::readCode(maxCode);
	string objectName = m_object[code - 1]->getId();
	m_object.erase(m_object.begin() + code - 1);
	cout << "\n������ " << objectName << " ������.\n\n";
}

SymbString* Factory::selectObject() const {
	int maxCode = (int)m_object.size();
	if (!maxCode) {
		cout << "\n��� ������������ ��������.\n\n";
		return 0;
	}
	cout << "\n�������� ������:\n";
	for (int i = 0; i < maxCode; ++i) {
		cout << i + 1 << ". ";
		cout << m_object[i]->getId() << "\n";
	}
	cout << "\n";
	int code = UI::readCode(maxCode);
	return m_object[code - 1];
}


void Factory::print() {
	int maxCode = (int)m_object.size();
	if (!maxCode) {
		cout << "\n��� ������������ ��������.\n\n";
		return;
	}
	cout << "\n";
	for (int i = 0; i < maxCode; ++i) {
		cout << i + 1 << ". " << m_object[i]->getId() << ": " << m_object[i]->getValue() << "\n";
	}
	cout << "\n";
}