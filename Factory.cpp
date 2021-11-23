#include <iostream> 
#include "Factory.h" 
#include "UI.h" 
#include "SymbString.h" 
#include "OctString.h" 
using namespace std;

void Factory::addObject() {
	std::cout << "\nВыберите тип объекта:\n";
	std::cout << "1. Символьная строка\n";
	std::cout << "2. Восьмеричная строка\n\n";
	int code = UI::readCode(2);

	string id;    std::cout << "\nВведите идентификатор объекта: ";  cin >> id;
	string value; std::cout << "Введите значение объекта: ";         cin >> value;
	SymbString* newObject;
	switch (code) {
	case 1: newObject = new SymbString(id, value); break;
	case 2:
		if (!isOctStringValue(value)) {
			cout << "\nОшибка: введенное значение не является восьмеричным числом!\n\n"; cin.get(); return;
		}
		newObject = new OctString(id, value);
		break;
	}
	m_object.push_back(newObject);
	std::cout << "\nОбъект " << newObject->getId() << " создан.\n\n";
	cin.get();
}

void Factory::deleteObject() {
	int maxCode = (int)m_object.size();
	if (!maxCode) {
		cout << "\nНет существующих объектов.\n\n";
		return;
	}

	cout << "\nВыберите объект для удаления:\n";
	for (int i = 0; i < maxCode; ++i)
		cout << i + 1 << ". " << m_object[i]->getId() << endl;
	cout << "\n";
	int code = UI::readCode(maxCode);
	string objectName = m_object[code - 1]->getId();
	m_object.erase(m_object.begin() + code - 1);
	cout << "\nОбъект " << objectName << " удален.\n\n";
}

SymbString* Factory::selectObject() const {
	int maxCode = (int)m_object.size();
	if (!maxCode) {
		cout << "\nНет существующих объектов.\n\n";
		return 0;
	}
	cout << "\nВыберите объект:\n";
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
		cout << "\nНет существующих объектов.\n\n";
		return;
	}
	cout << "\n";
	for (int i = 0; i < maxCode; ++i) {
		cout << i + 1 << ". " << m_object[i]->getId() << ": " << m_object[i]->getValue() << "\n";
	}
	cout << "\n";
}