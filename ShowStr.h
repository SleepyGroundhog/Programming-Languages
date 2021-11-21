// ShowStr.h 
#ifndef SHOWSTR_H
#define SHOWSTR_H

#include "Action.h" 

class ShowString : public Action {
public:
	ShowString() : m_name("Показать значение строки") {}
	void operate(SymbString*);
	const std::string& getName() const { return m_name; }
	void operator()(SymbString*);
private:
	std::string m_name;  // Обозначение операции
};
extern ShowString show_str;  // Определениие в ShowStr.cpp

#endif // SHOWSTR_H