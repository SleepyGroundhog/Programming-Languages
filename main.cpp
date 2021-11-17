#include "Money.h"
#include "BitString.h"

void testAddition(const Array& left, const Array& right) {
	Array* temp = left + right;
	cout << temp->tname() << "\n";
	//temp->print();
	//cout << "\n";
	delete temp;
}


int main() {
	new int[100];
	Money test1("200,00"), test2("100,00");
	//cout << test1 << " " << test2 << "\n";
	testAddition(test1, test2);
	//cout << test1 - test2 << "\n";
	//cout << test1 * test2 << "\n";
	//cout << test1 / test2 << "\n\n";
	
	//BitString test3("11110000"), test4("00110011");
	//cout << test3 + test4 << "\n";
	//cout << (test3 & test4) << "\n";
	//cout << (test3 ^ test4) << "\n";
	//cout << ~test3 << "\n";
	//cout << ~test4 << "\n";
	return 0;
}
