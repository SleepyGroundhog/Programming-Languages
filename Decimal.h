#pragma once
#include "List.h"
#include <string>

class Decimal
{
public:
	using Iterator = List<int>::Iterator;
	Decimal() { list.push_back(0); }

	friend std::istream& operator>> (std::istream& input, Decimal& octal);
	friend std::ostream& operator<< (std::ostream& output, const Decimal& octal);
	friend Decimal operator+(Decimal left, Decimal right);
	friend Decimal operator-(Decimal left, Decimal right);
	friend Decimal operator*(Decimal left, Decimal right);
	friend Decimal operator/(Decimal left, Decimal right);
	friend Decimal operator%(Decimal left, Decimal right);

	static int compare(const Decimal& left, const Decimal& right);

	class negative_result : public std::logic_error {
	public: negative_result() : logic_error("negative unsigned number") {} };

	class zero_division : public std::logic_error {
	public: zero_division() : logic_error("division by zero") {} };

	static void calculate(const Decimal& octal1, const Decimal& octal2);
	static Decimal read();

private:
	const static std::string sep;
	const static std::string alpha;
	const static int base = 10;
	List<int> list;

	void remove_leading_zeros() { while (list.size() > 1 && list.front() == 0) list.pop_front(); }
	static bool isInAlpha(std::string alphabet, char symbol) { return -1 != alphabet.find(symbol); }
	static void align(Decimal& right, Decimal& left, int count = 0);
	static int mul(int d1, int d2);
	friend Decimal operator*(Decimal right, int digit);

};