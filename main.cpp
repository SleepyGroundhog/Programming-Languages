#include "Array.h"
#include "List.h"
#include <iostream>

void _Array() {
	Array<int> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Array<int> b = { 0, -1, -2, -3, -4, -5, -6, -7, -8, -9 };
	b.push_back(a[a.size() - 1]);
	a.pop_back();
	a.print();
	b.print();

}

void _List() {
	List<int> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	List<int> b = { 0, -1, -2, -3, -4, -5, -6, -7, -8, -9 };
	b.push_back(*(a.end() - 1));
	a.pop_back();
	a.print();
	b.print();
}

int main() {
	_Array();
	_List();
	return 0;
}
