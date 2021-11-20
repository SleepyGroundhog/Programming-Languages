// SymbString.h
#ifndef SIMBSTRING_H
#define SIMBSTRING_H

#include <string>
#include "AString.h"

class SymbString : public AString {
public:
	SymbString(std::string _name) : name(_name) {}
	SymbString(std::string _name, std::string _val) :
		name(_name), val(_val) {}
	const std::string& GetName() const { return name; }
	const std::string& GetVal() const { return val; }
	int GetSize() const { return val.size(); }
private:
	std::string name;
	std::string val;
};

#endif // SIMBSTRING_H