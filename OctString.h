// HexString.h
#ifndef HEXSTRING_H
#define HEXSTRING_H

#include <string>
#include "SymbString.h"

bool isOctStringValue(std::string);

class OctString : public SymbString {
public:
	OctString(std::string _name) : m_name(_name) {}
	OctString(std::string, std::string);
	const std::string& getName() const { return m_name; }
	const std::string& getValue() const { return m_value; }
	int getSize() const { return m_value.size(); }
private:
	std::string m_name;
	std::string m_value;
};

#endif // HEXSTRING_H