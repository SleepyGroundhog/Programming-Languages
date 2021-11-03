#include <iostream>
#include "Money.h"

int main()
{
	Money a, b;
	int i;
	while (true) {
		cout << "Enter Money a and b or 0 to exit: ";
		cin >> a;
		if (a == Money()) { cout << "Exit\n"; break; }
		cin >> b;
		cout << "a = " << a << "\n";
		cout << "b = " << b << "\n";
		cout << "a + b = " << a + b << "\n";
		cout << "a - b = " << a - b << "\n";
		cout << "a * b = " << a * b << "\n";
		try { cout << "a / b = " << a / b << "\n"; } catch (exception exc) { cerr << exc.what() << "\n"; }
		cout << "a print like array: "; a.printArray();
		cout << "b print like array: "; b.printArray();
		cout << "Enter index to print element from a and b: ";
		cin >> i;
		try { cout << a[i] << "\n"; } catch (exception exc) { cerr << exc.what() << "\n"; }
		try { cout << b[i] << "\n"; } catch (exception exc) { cerr << exc.what() << "\n"; }
		cout << "\n";
	}
	
}
