#include <iostream>
#include "Money.h"
#include "byte.h"

void testUnsignedIntMathOperation()
{
	Money a("3110000000132647639486127461297864981236700");
	Money b("342658969458236523864981236700");
	int count_right = 0;
	const int test_amount = 4;
	count_right += (Money::uIntDiv(a, b) == Money("9076079359748") ? 1 : 0);
	count_right += (Money::uIntAdd(a, b) == Money("3110000000132990298455585697821729962473400") ? 1 : 0);
	count_right += (Money::uIntSub(a, b) == Money("3110000000132304980516669224774000000000000") ? 1 : 0);
	count_right += (Money::uIntMul(a, b) == Money("1065669395060568492667475765044932090219768967254924286533843061426890000") ? 1 : 0);
	cout << "unsigned int math operations: " << std::boolalpha << (count_right == test_amount) << "\n";
}

int main()
{
	testUnsignedIntMathOperation();
	Money a("3110000000132647639486127461297864981236700");
	Money b("342658969458236523864981236700");
	
	
	
	//cout << Money::compare(a, b) << "\n";
	//cout << Money::compare(b, a) << "\n";
	//cout << Money::compare(a, a) << "\n";


}
