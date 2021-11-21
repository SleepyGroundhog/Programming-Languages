// ShowDec.h
#ifndef SHOWDEC_H
#define SHOWDEC_H

#include "Action.h"

class ShowDec : public Action {
public:
	ShowDec() : m_name("�������� ���������� ������������� ������") {}
	void operate(SymbString*);
	const std::string& getName() const { return m_name; }
private:
	std::string m_name; // ����������� �������� 
};
extern ShowDec show_dec;  // ������������ � ShowDec.cpp

#endif // SHOWDEX_H