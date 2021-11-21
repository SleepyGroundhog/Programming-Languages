// Main.cpp 
#include <iostream>
#include "SymbString.h"
#include "OctString.h"
#include "Action.h" 
#include "ShowStr.h" 
#include "ShowDec.h"
#include "ShowBin.h"
#include "Factory.h"
#include "Menu.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "");
	Factory factory;
	Menu menu;
	Act operation;
	while ((operation = menu.selectJob()) != Exit) {
		switch (operation) {
		case AddObj: {
			factory.addObject();
			break;
		}
		case DeleteObj: {
			factory.deleteObject();
			break;
		}
		case DisplayObj: { // ����������� ������� - ���� �������
			SymbString* object = menu.selectObject(factory);
			Action* pAct = menu.selectAction(object);
			if (pAct)
				pAct->operate(object);
			break;
		} 
		case SumObj: {
			cout << "\n�������� �� �����������\n\n"; // �������� �������� - ��� ��������
			break;
		}
		}
	}
	return 0;
}