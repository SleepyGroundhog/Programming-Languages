// Menu.h 
#ifndef MENU_H
#define MENU_H

#include <vector>
#include "SymbString.h"
#include "Action.h"
#include "Factory.h" 

typedef enum { AddObj, DeleteObj, DisplayObj, SumObj, Exit } Act;

class Menu {
public:
	Menu();
	Act    selectJob() const;
	SymbString* selectObject(const Factory&) const;
	Action* selectAction(const SymbString*) const;
	// selectOperator(const SymbString*, const SymbString*);
	static int readCode(int);
private:
	std::vector<Action*> pAct;
};

#endif // MENU_H