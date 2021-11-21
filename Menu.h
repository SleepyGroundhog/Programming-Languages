// Menu.h 
#ifndef MENU_H
#define MENU_H

#include <vector>
#include "SymbString.h"
#include "Factory.h" 

typedef enum { AddObj, DeleteObj, DisplayObj, DisplayAllObj, SumObj, Exit } Operations;

class UI {
public:
	static Operations readOperation();
	static int        readCode(int);
};

#endif // MENU_H