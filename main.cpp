#include <iostream>
#include "Money.h"
#include "byte.h"




int main()
{
	Money a("3110000000132647639486127461297864981236700");
	Money b("342658969458236523864981236700");
	cout << Money::uIntDivision(a, b) << "\n";
	cout << Money::uIntAddition(a, b) << "\n";
	cout << Money::uIntSubtraction(a, b) << "\n";
	cout << Money::uIntMultiplication(a, b) << "\n";
}
