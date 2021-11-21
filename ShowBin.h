// ShowBin.h 
#ifndef SHOWBIN_H
#define SHOWBIN_H

#include "Action.h"

class ShowBin : public Action {
public:
	ShowBin() : m_name("ѕоказать двоичное представление строки") {}
	void operate(SymbString*);
	const std::string& getName() const { return m_name; }
private:
	std::string GetBinary(SymbString*) const;
	std::string m_name; // обозначение операции 
};
extern ShowBin show_bin;  // ќпределениие в ShowBin.cpp

#endif // SHOWBIN_H