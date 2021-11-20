// ShowBin.h 
#ifndef SHOWBIN_H
#define SHOWBIN_H

#include "Action.h"

class ShowBin : public Action {
public:
	ShowBin() : name("Show binary value") {}
	void Operate(AString*);
	const std::string& GetName() const { return name; }
private:
	std::string GetBinary(AString*) const;
	std::string name; // обозначение операции 
};
extern ShowBin show_bin;  // Определениие в ShowBin.cpp

#endif // SHOWBIN_H