#include "Array.h"
#include "List.h"
#include <iostream>

void _Array() {
	Array<int> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Array<int> b(a.begin() + 2, a.end() - 1);

	a.print();

	for (auto element : b)
		std::cout << element << " ";
	std::cout << "\n";

	a.clear();
	a.print();
	std::cout << a.size() << " " << a.capacity() << "\n";
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.print();
	std::cout << a.size() << " " << a.capacity() << "\n";

}

void _List() {
	List<int> b = { 1, 2, 3, 4, 5 };
	b.push_back(0), b.push_back(0), b.push_back(0), b.push_back(6), b.push_back(7), b.push_back(8), b.push_back(9);
	b.print();
	std::cout << b.size() << "\n";

	b.first();
	*b.iter() = 3;
	b.next(), *b.iter() = 41;
	b.next(), *b.iter() = 15;
	b.next(), *b.iter() = 92;
	b.next(), *b.iter() = 6;
	b.print();
	b.skip(9);
	std::cout << *b.iter() << "\n";
	*b.iter() = 14;
	b.pop_back(), b.pop_back(), b.pop_back(), b.pop_back();
	b.pop_back(), b.pop_back(), b.pop_back();
	b.print();
	
}

int main() {
	_Array();
	_List();
	return 0;
}
