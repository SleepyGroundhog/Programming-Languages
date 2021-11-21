// Factory.h
#ifndef FACTORY_H 
#define FACTORY_H

#include <vector>
#include "SymbString.h"

class Factory {
	friend class Menu;
public:
	Factory() {}
	void addObject();
	void deleteObject();
	SymbString* selectObject() const;
private:
	std::vector<SymbString*> object;
};

#endif // FACTORY_H 