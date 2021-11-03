#include <iostream>
#include "Hex.h"

int main()
{
	Hex a("1234567890ABCDEF");
	Hex b("123456");
	cout << a + b << "\n"; //1234567890BE0245 == 2468ACF121579BDE
	cout << a - b << "\n"; //1234567890999999
	cout << a * b << "\n"; //14B66D39FB5F7FA59BA4A == 14B66D39FB5F7FA59BA4A
	cout << a / b << "\n"; //10000069f72
}
//10000069f72