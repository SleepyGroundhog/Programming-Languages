#pragma once
#include "List.h"
#include <string>

class Octal
{
public:
	using Iterator = List<int>::Iterator;
	Octal() { list.push_back(0); } // инициализация нулем по умолчанию

	friend std::istream& operator>> (std::istream& input, Octal& octal);
	friend std::ostream& operator<< (std::ostream& output, const Octal& octal);
	friend Octal operator+(Octal left, Octal right);
	friend Octal operator-(Octal left, Octal right);
	friend Octal operator*(Octal left, Octal right);
	friend Octal operator/(Octal left, Octal right);
	friend Octal operator%(Octal left, Octal right);

	static int compare(const Octal& left, const Octal& right);

	class negative_result : public std::logic_error {
	public: negative_result() : logic_error("negative unsigned number") {} };

	class zero_division : public std::logic_error {
	public: zero_division() : logic_error("division by zero") {} };

private:
	const static std::string sep;
	const static std::string alpha;
	const static int base = 8;
	List<int> list;

	void remove_leading_zeros() { while (list.size() > 1 && list.front() == 0) list.pop_front(); }
	static bool isInAlpha(std::string alphabet, char symbol) { return -1 != alphabet.find(symbol); }
	static void align(Octal& right, Octal& left, int count = 0);
	static int mul(int d1, int d2);
	friend Octal operator*(Octal right, int digit);
	
};