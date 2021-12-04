#include "List.h"

void test_list() {
	List<int> list1;
	list1.print();
	
	std::cout << "\n*********\n\n";

	try { list1.pop_back(); }
	catch (std::exception e) { std::cout << e.what() << "\n"; }

	std::cout << "\n*********\n\n";

	list1.push_back(1);
	list1.push_back(2);
	list1.push_front(1);
	list1.push_front(2);
	for (auto& element : list1)
		std::cout << element << " ";

	std::cout << "\n\n*********\n\n";

	list1.pop_front();
	list1.print();

	std::cout << "\n*********\n\n";

	List<int> list2 = list1;
	list2.push_front(0);
	list2.print();

	std::cout << "\n*********\n\n";

	list2.push_front(1);
	list2.push_front(2);
	list2.push_front(3);
	list2.push_front(4);
	list2.push_front(5);
	list2.print();

	std::cout << "\n*********\n\n";

	
	list2.print();

}

int main() {
	test_list();
}