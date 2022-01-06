#include "Decimal.h"

int main() {
	Decimal octal1, octal2;
	octal1 = Decimal::read();
	octal2 = Decimal::read();
	Decimal::calculate(octal1, octal2);
	int code;
	while ((std::cin >> code) && code != 0) {
		switch (code) {
		case 1 : octal1 = Decimal::read();   break;
		case 2 : octal2 = Decimal::read();   break;
		default: std::cout << "Invalid code!\n"; continue;
		}
		Decimal::calculate(octal1, octal2);
	}
}