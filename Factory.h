// Factory.h
#ifndef FACTORY_H 
#define FACTORY_H

#include <vector>
#include "SymbString.h"

class Factory {
	friend class UI;
public:
	Factory() {}
	void        addObject();
	void        deleteObject();
	void        print();
	SymbString* selectObject() const;
private:
	std::vector<SymbString*> object;
};

#endif // FACTORY_H 