#include "Array.h"

#include "BitString.h"
using namespace std;


void caseArray(const Array& left, const Array& right) {
	cout << "array1                         : " << left << "\n";
	cout << "array2                         : " << right << "\n";
	cout << "array1 + array2                : " << left + right << "\n\n";
}

void caseBitString(const BitString& left, const BitString& right) {
	cout << "bitstring1 " << left << "bitstring2 " << right << "\n";
	cout << "bitstring1 & bitstring2 " << (left & right) << "\n";
	cout << "bitstring1 ! bitstring2 " << left + right  << "\n";
	cout << "bitstring1 ^ bitstring2 " <<(left ^ right) << "\n";
	cout << "! bitstring1 " << (~left) << " ! bitstring2 " <<(~right)       << "\n\n";
}

int main() {
	setlocale(LC_ALL, "");
	int arr_size;
	cout << "Введите длины массивов : ";           cin >> arr_size;
	Array array1(arr_size), array2(arr_size);
	
	BitString bitstring1, bitstring2;
	cout << "Введите array1 и array2 :\n";         cin >> array1 >> array2;
	
	bitstring1.fromString("1 1 1 1 0 0 1 1");
	bitstring2.fromString("0 0 1 0 1 0 1 1");
	
	//caseArray(array1, array2);
	
	caseBitString(bitstring1, bitstring2);

	int code = -1;
	while (code != 0) {
		cin >> code;
		switch (code) {
		case 1: cin >> array1;     caseArray(array1, array2);             break;
		case 2: cin >> array2;     caseArray(array1, array2);             break;
		
		case 5: cin >> bitstring1; caseBitString(bitstring1, bitstring2); break;
		case 6: cin >> bitstring2; caseBitString(bitstring1, bitstring2); break;
		case 0:                                                           break;
		default: cout << "Неверный код операции!\n";					      break;
		}
	}
	return 0;
}