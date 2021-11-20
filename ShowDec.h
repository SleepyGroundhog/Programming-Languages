// ShowDec.h
#ifndef SHOWDEC_H
#define SHOWDEC_H

#include "Action.h"

class ShowDec : public Action {
public:
	ShowDec() : name("Show decimal value") {}
	void Operate(AString*);
	const std::string& GetName() const { return name; }
private:
	std::string name; // ����������� �������� 
};
extern ShowDec show_dec;  // ������������ � ShowDec.cpp

#endif // SHOWDEX_H