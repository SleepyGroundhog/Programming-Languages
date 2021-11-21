// ShowDec.h
#ifndef SHOWDEC_H
#define SHOWDEC_H

#include "Action.h"

class ShowDec : public Action {
public:
	ShowDec() : m_name("ѕоказать дес€тичное представление строки") {}
	void operate(SymbString*);
	const std::string& getName() const { return m_name; }
private:
	std::string m_name; // обозначение операции 
};
extern ShowDec show_dec;  // ќпределениие в ShowDec.cpp

#endif // SHOWDEX_H