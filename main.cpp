// Main.cpp 
#include <iostream>
#include "Menu.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "");
	Factory factory;
	Operations operation;
	SymbString* object1, * object2;
	while ((operation = UI::readOperation()) != Exit) {
		switch (operation) {
		case AddObj:
			factory.addObject();
			break;
		case DeleteObj:
			factory.deleteObject();
			break;
		case DisplayObj:
			object1 = factory.selectObject();
			if (object1)
				object1->showString();
			break;
		case DisplayAllObj:
			factory.print();
			break;
		case SumObj:
			object1 = factory.selectObject();
			if (object1) {
				object2 = factory.selectObject();
				if (object1 && object2) {
					SymbString* temp = (*object1 + *object2);
					temp->showString();
					delete temp;
				}
			}
			break;
		}
	}
	return 0;
}