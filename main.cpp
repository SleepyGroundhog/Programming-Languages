#include "Array.h"
#include <iostream>

int main()
{
	Array<int> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Array<int> b(a.begin() + 2, a.end() - 1);
	a.print();
	b.print();

	std::cout << b[0] << " " << b[2] << " " << b[3] << " " << b[b.size() - 3] << " " << b[b.size() - 1] << "\n";

	return 0;
}
