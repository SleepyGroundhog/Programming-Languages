// HexString.h
#ifndef HEXSTRING_H
#define HEXSTRING_H

#include <string>
#include "AString.h"

const std::string alph = "0123456789ABCDEF";
bool IsHexStrVal(std::string);

class HexString : public AString {
public:
	HexString(std::string _name) : name(_name) {}
	HexString(std::string, std::string);
	const std::string& GetName() const { return name; }
	const std::string& GetVal() const { return val; }
	int GetSize() const { return val.size(); }
private:
	std::string name;
	std::string val;
};

#endif // HEXSTRING_H