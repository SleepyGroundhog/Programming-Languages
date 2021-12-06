#include "List.h"
#include "Octal.h"

class Ui {
public:
	static void count_and_print(const Octal& octal1, const Octal& octal2) {
		using std::cout;

		         cout << "Octal1 = "     << octal1 << ", ";
		         cout << "Octal2 = "     << octal2 << "\n";
		         cout << octal1 << " + " << octal2 << " = " << octal1 + octal2 << "\n";
		try {    cout << octal1 << " - " << octal2 << " = " << octal1 - octal2 << "\n"; }
		catch    (Octal::negative_result error) { cout << "Error: " << error.what() << "!\n"; }
		         cout << octal1 << " * " << octal2 << " = " << octal1 * octal2 << "\n";
		try {    cout << octal1 << " / " << octal2 << " = " << octal1 / octal2 << "\n";
			     cout << octal1 << " % " << octal2 << " = " << octal1 % octal2 << "\n"; }
		catch    (Octal::zero_division   error) { cout << "Error: " << error.what() << "!\n"; }
		
		switch   (Octal::compare(octal1, octal2)) {
		case -1: cout << octal1 << " < " << octal2 << "\n"; break;
		case  0: cout << octal1 << " = " << octal2 << "\n"; break;
		case  1: cout << octal1 << " > " << octal2 << "\n"; break;
		}
	}

	static Octal read_octal() {
		Octal octal;
		bool reading = true;
		while (reading) {
			try {
				std::cin >> octal;
				reading = false;
			} catch (std::invalid_argument error) {
				std::cout << "Error: " << error.what() << "! ";
				std::cout << "Please, input number again.\n";
			}
		}
		return octal;
	}

};