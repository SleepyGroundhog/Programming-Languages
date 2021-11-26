#include "Array.h"
#include "List.h"
#include <iostream>

void _Array() {
	Array<int> a = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	std::cout << *(a.end() - 1) << "\n";

}

void _List() {
	List<int> b = { 3, 14};

	std::cout << "Magic\n";
	//b.print();

	List<int>::Iterator iter = b.begin();

	for (auto& element : b)
		std::cout << element << "\n";


}

int main() {
	_Array();
	//_List();
	return 0;
}
