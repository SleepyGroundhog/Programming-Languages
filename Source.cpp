#include "List.h"

int main() {

	List<int> list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.pop_back();
	list.pop_back();
	list.print();



}