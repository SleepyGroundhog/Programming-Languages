// Menu.cpp
#include <iostream>
#include "AString.h" 
#include "SymbString.h"
#include "HexString.h" 
#include "Menu.h" 
using namespace std;

Menu::Menu(vector<Action*> _pAct) : pAct(_pAct) {}

JobMode Menu::SelectJob() const {
	cout << "======================================\n";
	cout << "Select one of the following job modes:\n";
	cout << "1. Add object"                    << endl;
	cout << "2. Delete object"                 << endl;
	cout << "3. Work with object"              << endl;
	cout << "4. Exit"                          << endl;
	int item = SelectItem(4);
	return (JobMode)(item - 1);
}

AString* Menu::SelectObject(const Factory& fctry) const
{
	int nItem = fctry.pObj.size();
	if (!nItem) {
		cout << "There are no objects." << endl;
		cin.get();
		return 0;
	}
	cout << "--------------------------------------\n";
	cout << "Select one of the following Object:\n";
	for (int i = 0; i < nItem; ++i) {
		cout << i + 1 << ". ";
		cout << fctry.pObj[i]->GetName() << endl;
	}
	int item = SelectItem(nItem);
	return fctry.pObj[item - 1];
}

Action* Menu::SelectAction(const AString* pObj) const {
	if (!pObj) return 0;
	int nItem = pAct.size();
	cout << "--------------------------------------\n";
	cout << "Select one of the following Actions:\n";
	for (int i = 0; i < nItem; ++i) {
		cout << i + 1 << ". ";
		cout << pAct[i]->GetName() << endl;
	}
	int item = SelectItem(nItem);
	return pAct[item - 1];
}

int Menu::SelectItem(int nItem) {
	cout << "--------------------------------------\n";
	int item;
	while (true) {
		cin >> item;
		if ((item > 0) && (item <= nItem) && (cin.peek() == '\n')) {
			cin.get();
			break;
		}
		else {
			cout << "Error (must be number from 1 to " << nItem << "): " << endl;
			cin.clear();
			while (cin.get() != '\n') {};
		}
	}
	return item;
}