// Factory.h
#ifndef FACTORY_H 
#define FACTORY_H

#include <vector>
#include "AString.h"

class Factory {
	friend class Menu;
public:
	Factory() {}
	void AddObject();
	void DeleteObject();
private:
	std::vector<AString*> pObj;
};

#endif // FACTORY_H 