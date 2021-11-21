// Action.h
#ifndef ACTION_H 
#define ACTION_H

#include "SymbString.h" 

class Action {
public:
	virtual ~Action() {}
	virtual void operate(SymbString*) = 0;
	virtual const std::string& getName() const = 0;
protected:
	long GetDecimal(SymbString* object) const;
};

#endif // ACTION_H