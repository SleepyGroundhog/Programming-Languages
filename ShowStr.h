// ShowStr.h 
#ifndef SHOWSTR_H
#define SHOWSTR_H

#include "Action.h" 

class ShowStr : public Action {
public:
	ShowStr() : name("Show string value") {}
	void Operate(AString*);
	const std::string& GetName() const { return name; }
private:
	std::string name;  // Обозначение операции
};
extern ShowStr show_str;  // Определениие в ShowStr.cpp

#endif // SHOWSTR_H