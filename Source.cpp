#include "Ui.h"

int main() {
	Octal octal1, octal2;
	octal1 = Ui::read_octal();
	octal2 = Ui::read_octal();
	Ui::count_and_print(octal1, octal2);
	int code;
	while ((std::cin >> code) && code != 0) {
		switch (code) {
		case 1 : octal1 = Ui::read_octal();   break;
		case 2 : octal2 = Ui::read_octal();   break;
		default: std::cout << "Invalid code!\n"; continue;
		}
		Ui::count_and_print(octal1, octal2);
	}
}