﻿#include <iostream>
#include "Money.h"
#include "byte.h"
#include <vector>

class NoPointTests
{
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
		const int test_amount = 20 * 6;
		vector<string> a = { "1", "-1", "1", "-1",  "2", "-2", "2", "-2", "-1",  "1", "1", "-1", "10", "-10", "10", "-10",  "1",   "1", "-1",  "-1" };
		vector<string> b = { "-1",  "1", "1", "-1", "-1",  "1", "1", "-1",  "2", "-2", "2", "-2",  "1",   "1", "-1",  "-1", "10", "-10", "10", "-10" };
		for (int i = 0; i < 20; ++i) {
			count_right += (((Money(a[i]) == Money(b[i])) == (stoi(a[i]) == stoi(b[i]))) ? 1 : 0);
			count_right += (((Money(a[i]) != Money(b[i])) == (stoi(a[i]) != stoi(b[i]))) ? 1 : 0);
			count_right += (((Money(a[i]) >= Money(b[i])) == (stoi(a[i]) >= stoi(b[i]))) ? 1 : 0);
			count_right += (((Money(a[i]) <= Money(b[i])) == (stoi(a[i]) <= stoi(b[i]))) ? 1 : 0);
			count_right += (((Money(a[i]) > Money(b[i])) == (stoi(a[i]) > stoi(b[i]))) ? 1 : 0);
			count_right += (((Money(a[i]) < Money(b[i])) == (stoi(a[i]) < stoi(b[i]))) ? 1 : 0);
		}
		cout << "signed int comparisons operators: " << std::boolalpha << (count_right == test_amount) << endl;
	}

	void testSignedIntAddAndSubMathOperation() {
		int count_right = 0;
		const int test_amount = 20 * 2;
		vector<string> a = { "1", "-1", "1", "-1",  "2", "-2", "2", "-2", "-1",  "1", "1", "-1", "10", "-10", "10", "-10",  "1",   "1", "-1",  "-1" };
		vector<string> b = { "-1",  "1", "1", "-1", "-1",  "1", "1", "-1",  "2", "-2", "2", "-2",  "1",   "1", "-1",  "-1", "10", "-10", "10", "-10" };
		for (int i = 0; i < 20; ++i) {
			count_right += ((stoi((Money(a[i]) + Money(b[i])).toString()) == (stoi(a[i]) + stoi(b[i]))) ? 1 : 0);
			count_right += ((stoi((Money(a[i]) - Money(b[i])).toString()) == (stoi(a[i]) - stoi(b[i]))) ? 1 : 0);
		}
		cout << "signed int addition and subtitute operators: " << std::boolalpha << (count_right == test_amount) << endl;
	}

	void testSignedIntDivAndMulMathOperation() {
		int count_right = 0;
		const int test_amount = 20 * 2;
		vector<string> a = { "123", "-123", "1324", "-123",  "243", "-223", "32", "-234", "-123",  "125", "165", "-16", "1076", "-106", "107", "-1067",  "1",   "133", "1",  "0" };
		vector<string> b = { "-143",  "134", "134", "-134", "-431",  "14", "14", "-134",  "243", "-243", "278", "-278",  "1778",   "177", "-16",  "-1", "1", "-1", "10", "-103" };

		for (int i = 0; i < 20; ++i) {
			count_right += ((stoi((Money(a[i]) * Money(b[i])).toString()) == (stoi(a[i]) * stoi(b[i]))) ? 1 : 0);
			count_right += ((stoi((Money(a[i]) / Money(b[i])).toString()) == (stoi(a[i]) / stoi(b[i]))) ? 1 : 0);
		}
		cout << "signed multiplication and division operators: " << std::boolalpha << (count_right == test_amount) << endl;
	}

	void start() {
		testUnsignedIntMathOperation();
		testSignedIntCompareOperation();
		testSignedIntAddAndSubMathOperation();
		testSignedIntDivAndMulMathOperation();
	}
};


int main()
{
	Money a, b;
	while (true) {
		cin >> a >> b;
		cout << "a = " << a << "\n";
		cout << "b = " << b << "\n";
		cout << "a + b = " << a + b << "\n";
		cout << "a - b = " << a - b << "\n";
		cout << "a * b = " << a * b << "\n";
		try {
			cout << "a / b = " << a / b << "\n";
		}
		catch (exception exc) { cerr << exc.what() << "\n"; }
		
	}
	


}
