// Menu.cpp
#include <iostream>
#include <string>
#include "SymbString.h"
#include "OctString.h" 
#include "Menu.h"

#include "ShowStr.h"
#include "ShowBin.h"
#include "ShowDec.h"

using namespace std;

Menu::Menu() {
	Action* pActs[] = { &show_str, &show_dec, &show_bin };
	vector<Action*> actions(pActs, pActs + sizeof(pActs) / sizeof(Action*));
	pAct = actions;
}

Act Menu::selectJob() const {
	cout << "�������� ��������:\n";
	cout << "1. ������� ������\n";
	cout << "2. ������� ������\n";
	cout << "3. ���������� ������\n";
	cout << "4. ������� ��� �������\n";
	cout << "5. �����\n\n";
	int code = readCode(5);
	return (Act)(code - 1);
}


SymbString* Menu::selectObject(const Factory& fctry) const {
	int maxCode = fctry.object.size();
	if (!maxCode) {
		cout << "\n��� ������������ ��������.\n\n";
		return 0;
	}
	cout << "�������� ������:\n";
	for (int i = 0; i < maxCode; ++i) {
		cout << i + 1 << ". ";
		cout << fctry.object[i]->getName() << endl;
	}
	int code = readCode(maxCode);
	return fctry.object[code - 1];
}

Action* Menu::selectAction(const SymbString* object) const {
	if (!object) return 0;
	int maxCode = pAct.size();
	cout << "�������� �������� �����������:\n";
	for (int i = 0; i < maxCode; ++i) {
		cout << i + 1 << ". ";
		cout << pAct[i]->getName() << endl;
	}
	int code = readCode(maxCode);
	return pAct[code - 1];
}

int Menu::readCode(int maxCode) {
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