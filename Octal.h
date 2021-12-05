#pragma once
#include "List.h"
#include <string>

class Octal
{
public:
	using Iterator = List<int>::Iterator;
	Octal() { list.push_back(0); } // инициализация нулем по умолчанию

	friend std::istream& operator>> (std::istream& input, Octal& octal) {
		
		while (isInAlpha(sep, input.peek())) input.get(); // очистка потока от символов разделителей
		octal.list.clear();

		char buf;
		while (buf = input.get())
		{
			if (isInAlpha(alpha, buf))
				octal.list.push_back(buf - '0');

			else if (isInAlpha(sep, buf))
				break;

			else {
				octal.list.clear();
				octal.list.push_back(0);
				while (input.peek() != '\n') input.get();
				throw std::invalid_argument("symbol \"" + std::string(1, buf) + "\" is not octal digit");
			}	
		}
		octal.remove_leading_zeros();
		return input;
	}
 
	friend std::ostream& operator<< (std::ostream& output, const Octal& octal) {
		octal.list.print(std::cout, "", "");
		return output;
	}

	friend Octal operator+(Octal left, Octal right) {
		align(left, right, 1);
		Iterator L = left.list.end() - 1, R = right.list.end() - 1;
		while (L != left.list.begin())
			*L += *R, *(L - 1) += *L / base, *L %= base, --L, --R;
		left.remove_leading_zeros();
		return left;
	}

	friend Octal operator-(Octal left, Octal right);
	friend Octal operator*(Octal left, Octal right);
	friend Octal operator/(Octal left, Octal right);
	friend Octal operator%(Octal left, Octal right);

	class negative_result : public std::logic_error {
	public: negative_result() : logic_error("negative unsigned number") {} };
	
	class zero_division : public std::logic_error {
	public: zero_division() : logic_error("division by zero") {} };

	static int compare(const Octal& left, const Octal& right);

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