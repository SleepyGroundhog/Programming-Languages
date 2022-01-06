#include "Decimal.h"

using Iterator = List<int>::Iterator;

const std::string Decimal::sep   = "\n \t";
const std::string Decimal::alpha = "0123456789";


int Decimal::mul(int d1, int d2) {
	return d1 * d2;
}

// Дополняет оба числа незначащими нулями до равной длинны с дополнимельными count нулями
void Decimal::align(Decimal& left, Decimal& right, int count) {
	int max_size = std::max(left.list.size(), right.list.size()) + count;
	while (left.list.size()  < max_size)  left.list.push_front(0);
	while (right.list.size() < max_size) right.list.push_front(0);
}

// left >  right : return  1;
// left == right : return  0;
// left <  right : return -1.
int Decimal::compare(const Decimal& left, const Decimal& right) {	
	if (left.list.size() != right.list.size()) {
		return (left.list.size() > right.list.size()) ? 1 : -1; // разные длины чисел сравниваем,
	}															// основываясь на длине										
	Iterator L = left.list.begin(), R = right.list.begin();
	for (; L != left.list.end() && R != right.list.end(); ++L, ++R) {
		     if ( *L > *R ) return  1;
		else if ( *L < *R ) return -1;
	}

	return 0;
}

std::istream& operator>> (std::istream& input, Decimal& octal) {

	while (Decimal::isInAlpha(Decimal::sep, input.peek())) input.get(); // очистка потока от символов разделителей
	octal.list.clear();

	char buf;
	while (buf = input.get())
	{
		if (Decimal::isInAlpha(Decimal::alpha, buf))
			octal.list.push_back(buf - '0');

		else if (Decimal::isInAlpha(Decimal::sep, buf))
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

std::ostream& operator<< (std::ostream& output, const Decimal& octal) {
	octal.list.print(std::cout, "", "");
	return output;
}

Decimal operator+(Decimal left, Decimal right) {
	Decimal::align(left, right, 1);
	Iterator L = left.list.end() - 1, R = right.list.end() - 1;
	while (L != left.list.begin())
		*L += *R, * (L - 1) += *L / Decimal::base, * L %= Decimal::base, --L, --R;
	left.remove_leading_zeros();
	return left;
}

Decimal operator-(Decimal left, Decimal right) {
	if (Decimal::compare(left, right) == -1) throw (Decimal::negative_result());
	Decimal::align(left, right, 1);
	Iterator L = left.list.end() - 1, R = right.list.end() - 1;
	while (L != left.list.begin()) {
		*L -= *R;
		if (*L < 0) *L += Decimal::base, * (L - 1) -= 1;
		--L, --R;
	}
	left.remove_leading_zeros();
	return left;
}

Decimal operator*(Decimal left, int right) {
	assert(Decimal::isInAlpha(Decimal::alpha, right + '0') && "right is not octal digit");
	Decimal res;
	left.list.push_front(0);
	while (res.list.size() < left.list.size()) res.list.push_back(0);
	Iterator L = left.list.end() - 1;
	Iterator I = res.list.end() - 1;
	for (; L != left.list.begin(); --L, --I) {
		*I += Decimal::mul(*L, right) % 10;
		*(I - 1) += Decimal::mul(*L, right) / 10;
	}
	res.remove_leading_zeros();
	return res;
}

Decimal operator/(Decimal left, Decimal right) {
	if (right.list.size() == 1 && right.list.back() == 0) {
		throw (Decimal::zero_division());
	}
	Decimal    res, sub;
	int      count_div;
	Iterator L           = left.list.begin();
	sub.list.pop_back();
	while (L != left.list.end()) {
		sub.list.push_back(*L);
		sub.remove_leading_zeros();
		count_div = 0;
		while (Decimal::compare(sub, right) != -1) {
			sub = sub - right, ++count_div;
			sub.remove_leading_zeros();
		}
		res.list.push_back(count_div);
		++L;
	}
	res.remove_leading_zeros();
	return res;
}

Decimal operator*(Decimal left, Decimal right) {
	Decimal res;
	if (Decimal::compare(left, right) == -1) std::swap(left, right);
	right.list.push_front(0);
	Iterator R = right.list.begin();
	while (R != right.list.end()) {
		res.list.push_back(0);
		res = res + (left * *R);
		++R;
	}
	return res;
}

Decimal operator%(Decimal left, Decimal right) {
	Decimal div = left / right;
	return left - div * right;
}

void Decimal::calculate(const Decimal& octal1, const Decimal& octal2) {
	using std::cout;

	cout << "Octal1 = " << octal1 << ", ";
	cout << "Octal2 = " << octal2 << "\n";
	cout << octal1 << " + " << octal2 << " = " << octal1 + octal2 << "\n";
	try { cout << octal1 << " - " << octal2 << " = " << octal1 - octal2 << "\n"; }
	catch (Decimal::negative_result error) { cout << "Error: " << error.what() << "!\n"; }
	cout << octal1 << " * " << octal2 << " = " << octal1 * octal2 << "\n";
	try {
		cout << octal1 << " / " << octal2 << " = " << octal1 / octal2 << "\n";
		cout << octal1 << " % " << octal2 << " = " << octal1 % octal2 << "\n";
	}
	catch (Decimal::zero_division   error) { cout << "Error: " << error.what() << "!\n"; }

	switch (Decimal::compare(octal1, octal2)) {
	case -1: cout << octal1 << " < " << octal2 << "\n"; break;
	case  0: cout << octal1 << " = " << octal2 << "\n"; break;
	case  1: cout << octal1 << " > " << octal2 << "\n"; break;
	}
}

Decimal Decimal::read() {
	Decimal octal;
	bool reading = true;
	while (reading) {
		try {
			std::cin >> octal;
			reading = false;
		}
		catch (std::invalid_argument error) {
			std::cout << "Error: " << error.what() << "! ";
			std::cout << "Please, input number again.\n";
		}
	}
	return octal;
}