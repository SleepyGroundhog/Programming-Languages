// HexString.h
#ifndef HEXSTRING_H
#define HEXSTRING_H

#include <string>
#include "SymbString.h"

bool isOctStringValue(std::string);

class OctString : public SymbString {
public:
	OctString(std::string id) : SymbString(id) {}
	OctString(std::string, std::string);
	const std::string& getId() const { return m_id; }
	const std::string& getValue() const { return m_value; }
	int                getSize() const { return (int)m_value.size(); }
	SymbString* operator+(SymbString object2);
};

#endif // HEXSTRING_H