// Menu.cpp
#include <iostream>
#include <string>
#include "SymbString.h"
#include "OctString.h" 
#include "Menu.h"

using namespace std;

Operations UI::readOperation() {
	cout << "Выберите операцию:\n";
	cout << "1. Создать объект\n";
	cout << "2. Удалить объект\n";
	cout << "3. Отобразить объект\n";
	cout << "4. Отобразить все объекты\n";
	cout << "5. Сложить два объекта\n";
	cout << "6. Выйти\n\n";
	int code = readCode(6);
	return (Operations)(code - 1);
}

int UI::readCode(int maxCode) {
	int code;
	string input;
	while (true) {
		cout << ">>> "; getline(cin, input);
		try { code = stoi(input); } catch (...) { code = -1; }
		if ((code > 0) && (code <= maxCode)) {
			break;
		} else {
			cout << "\nОшибка: необходимо ввести код от 1 до " << maxCode << " :\n\n";
			cin.clear();
		}
	}
	return code;
}