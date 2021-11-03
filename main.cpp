#include <iostream>
#include "Money.h"
#include "byte.h"
#include <vector>


void testUnsignedIntMathOperation() {
	Money a("3110000000132647639486127461297864981236700");
	Money b("342658969458236523864981236700");
	int count_right = 0;
	const int test_amount = 4;
	count_right += (Money::uIntDiv(a, b) == Money("9076079359748") ? 1 : 0);
	count_right += (Money::uIntAdd(a, b) == Money("3110000000132990298455585697821729962473400") ? 1 : 0);
	count_right += (Money::uIntSub(a, b) == Money("3110000000132304980516669224774000000000000") ? 1 : 0);
	count_right += (Money::uIntMul(a, b) == Money("1065669395060568492667475765044932090219768967254924286533843061426890000") ? 1 : 0);
	cout << "unsigned int math operations: " << std::boolalpha << (count_right == test_amount) << endl;
}

void testSignedIntCompareOperation() {
	int count_right = 0;
	const int test_amount = 120;
	vector<string> a = {  "1", "-1", "1", "-1",  "2", "-2", "2", "-2", "-1",  "1", "1", "-1", "10", "-10", "10", "-10",  "1",   "1", "-1",  "-1" };
	vector<string> b = { "-1",  "1", "1", "-1", "-1",  "1", "1", "-1",  "2", "-2", "2", "-2",  "1",   "1", "-1",  "-1", "10", "-10", "10", "-10" };
	for (int i = 0; i < test_amount / 6; ++i) {
		count_right += (((Money(a[i]) == Money(b[i])) == (stoi(a[i]) == stoi(b[i]))) ? 1 : 0);
		count_right += (((Money(a[i]) != Money(b[i])) == (stoi(a[i]) != stoi(b[i]))) ? 1 : 0);
		count_right += (((Money(a[i]) >= Money(b[i])) == (stoi(a[i]) >= stoi(b[i]))) ? 1 : 0);
		count_right += (((Money(a[i]) <= Money(b[i])) == (stoi(a[i]) <= stoi(b[i]))) ? 1 : 0);
		count_right += (((Money(a[i]) >  Money(b[i])) == (stoi(a[i]) >  stoi(b[i]))) ? 1 : 0);
		count_right += (((Money(a[i]) <  Money(b[i])) == (stoi(a[i]) <  stoi(b[i]))) ? 1 : 0);
	}
	cout << "signed int comparisons operators: " << std::boolalpha << (count_right == test_amount) << endl;
}

int main()
{
	testUnsignedIntMathOperation();
	testSignedIntCompareOperation();
	//Money a("3110000000132647639486127461297864981236700");
	//Money b("-342658969458236523864981236700");
	//cout << a << " " << a.isNegative() << "\n";
	//cout << b << " " << b.isNegative() << "\n";
	
	
	//cout << Money::compare(a, b) << "\n";
	//cout << Money::compare(b, a) << "\n";
	//cout << Money::compare(a, a) << "\n";


}
