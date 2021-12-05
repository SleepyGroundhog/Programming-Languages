#include "Octal.h"

using Iterator = List<int>::Iterator;

const std::string Octal::sep   = "\n \t";
const std::string Octal::alpha = "01234567";

// Таблица умножения для 8-ричных чисел
int Octal::mul(int d1, int d2) {
	const static unsigned char table[8][8] = {
		{0, 0,  0,  0,  0,  0,  0,   0},
		{0, 1,  2,  3,  4,  5,  6,   7},
		{0, 2,  4,  6, 10, 12, 14,  16},
		{0, 3,  6, 11, 14, 17, 22,  25},
		{0, 4, 10, 14, 20, 24, 30,  34},
		{0, 5, 12, 17, 24, 31, 36,  43},
		{0, 6, 14, 22, 30, 36, 44,  52},
		{0, 7, 16, 25, 34, 43, 52,  61},
	};
	return table[d1][d2];
}

// Дополняет оба числа незначащими нулями до равной длинны с дополнимельными count нулями
void Octal::align(Octal& left, Octal& right, int count) {
	int max_size = std::max(left.list.size(), right.list.size()) + count;
	while (left.list.size()  < max_size)  left.list.push_front(0);
	while (right.list.size() < max_size) right.list.push_front(0);
}

// left >  right : return  1;
// left == right : return  0;
// left <  right : return -1.
int Octal::compare(const Octal& left, const Octal& right) {	
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

Octal operator-(Octal left, Octal right) {
	if (Octal::compare(left, right) == -1) throw (Octal::negative_result());
	Octal::align(left, right, 1);
	Iterator L = left.list.end() - 1, R = right.list.end() - 1;
	while (L != left.list.begin()) {
		*L -= *R;
		if (*L < 0) *L += Octal::base, * (L - 1) -= 1;
		--L, --R;
	}
	left.remove_leading_zeros();
	return left;
}

Octal operator*(Octal left, int right) {
	assert(Octal::isInAlpha(Octal::alpha, right + '0') && "right is not octal digit");
	Octal res;
	left.list.push_front(0);
	while (res.list.size() < left.list.size()) res.list.push_back(0);
	Iterator L = left.list.end() - 1;
	Iterator I = res.list.end() - 1;
	for (; L != left.list.begin(); --L, --I) {
		*I += Octal::mul(*L, right) % 10;
		*(I - 1) += Octal::mul(*L, right) / 10;
	}
	res.remove_leading_zeros();
	return res;
}

Octal operator/(Octal left, Octal right) {
	if (right.list.size() == 1 && right.list.back() == 0) {
		throw (Octal::zero_division());
	}
	Octal    res, sub;
	int      count_div;
	Iterator L           = left.list.begin();
	sub.list.pop_back();
	while (L != left.list.end()) {
		sub.list.push_back(*L);
		sub.remove_leading_zeros();
		count_div = 0;
		while (Octal::compare(sub, right) != -1) {
			sub = sub - right, ++count_div;
			sub.remove_leading_zeros();
		}
		res.list.push_back(count_div);
		++L;
	}
	res.remove_leading_zeros();
	return res;
}

Octal operator*(Octal left, Octal right) {
	Octal res;
	if (Octal::compare(left, right) == -1) std::swap(left, right);
	right.list.push_front(0);
	Iterator R = right.list.end() - 1;
	while (R != right.list.begin()) {
		res.list.push_back(0);
		res = res + (left * *R);
		--R;
	}
	return res;
}

Octal operator%(Octal left, Octal right) {
	Octal div = left / right;
	return left - div * right;
}