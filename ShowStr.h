// ShowStr.h 
#ifndef SHOWSTR_H
#define SHOWSTR_H

#include "Action.h" 

class ShowString : public Action {
public:
	ShowString() : m_name("�������� �������� ������") {}
	void operate(SymbString*);
	const std::string& getName() const { return m_name; }
	void operator()(SymbString*);
private:
	std::string m_name;  // ����������� ��������
};
extern ShowString show_str;  // ������������ � ShowStr.cpp

#endif // SHOWSTR_H