#ifndef SIMBSTRING_H
#define SIMBSTRING_H

#include <string>

class SymbString {
public:
	virtual ~SymbString() {}
	SymbString(std::string id = "") : m_id(id) {}
	SymbString(std::string id, std::string value) : m_id(id), m_value(value) {}
	virtual const std::string& getId() const { return m_id; }
	virtual const std::string& getValue() const { return m_value; }
	virtual int                getSize() const { return (int)m_value.size(); }
	void                       showString() { std::cout << "\n" << getId() << ": " << getValue() << "\n"; }
	virtual SymbString* operator+(SymbString object2) { SymbString* result = new SymbString(getId() + " + " + object2.getId(), getValue() + object2.getValue()); return result; }
protected:
	std::string m_id;
	std::string m_value;
};

#endif // SIMBSTRING_H