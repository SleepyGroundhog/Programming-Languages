// SymbString.h
#ifndef SIMBSTRING_H
#define SIMBSTRING_H

#include <string>

class SymbString {
public:
	virtual ~SymbString() {}
	SymbString(std::string _name = "") : m_name(_name) {}
	SymbString(std::string _name, std::string _val) :
		m_name(_name), m_value(_val) {}
	virtual const std::string& getName() const { return m_name; }
	virtual const std::string& getValue() const { return m_value; }
	virtual int getSize() const { return m_value.size(); }
private:
	std::string m_name;
	std::string m_value;
};

#endif // SIMBSTRING_H