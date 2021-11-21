// ShowBin.h 
#ifndef SHOWBIN_H
#define SHOWBIN_H

#include "Action.h"

class ShowBin : public Action {
public:
	ShowBin() : m_name("�������� �������� ������������� ������") {}
	void operate(SymbString*);
	const std::string& getName() const { return m_name; }
private:
	std::string GetBinary(SymbString*) const;
	std::string m_name; // ����������� �������� 
};
extern ShowBin show_bin;  // ������������ � ShowBin.cpp

#endif // SHOWBIN_H