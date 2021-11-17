#include "Money.h"
#include "BitString.h"

int main() {
	
	Array a(2), b(4);
	cin >> a >> b;
	cout << a << " " << b << "\n";
	Array* c = a.sum(b);
	cout << *c << "\n";

	return 0;
}
