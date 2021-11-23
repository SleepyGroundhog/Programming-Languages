#include <iostream>
#include <string>
#include "SymbString.h"
#include "OctString.h" 
#include "UI.h"

using namespace std;

Operations UI::readOperation() {
	cout << "������� ��� ��������:\n\n";
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
			cout << "\n������: ���������� ������ ��� �� 1 �� " << maxCode << " :\n\n";
			cin.clear();
		}
	}
	return code;
}