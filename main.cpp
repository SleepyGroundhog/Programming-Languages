#include <exception>
#include <iostream>
#include <string>
using namespace std;

class InvalidHours {};
class InvalidMinutes {};

class InvalidHours_std : public invalid_argument {
private:
	string m_error = "Error ¹–1 - nedopustimoe chislo chasov!!!!";
public:
	InvalidHours_std() : invalid_argument("") {}
	const char* what() const { return m_error.c_str(); }
};

class InvalidMinutes_std : public invalid_argument {
private:
	string m_error = "Error ¹–2 - nedopustimoe chislo minut!!!!";
public:
	InvalidMinutes_std() : invalid_argument("") {}
	const char* what() const { return m_error.c_str(); }
};

int seconds_std(int hours, int minutes) throw(InvalidHours_std, InvalidMinutes_std) {
	if (hours >= 24 || hours < 0)
		throw InvalidHours_std();
	else if (minutes >= 60 || minutes < 0)
		throw InvalidMinutes_std();
	return hours * 60 * 60 + minutes * 60;
}

int seconds(int hours, int minutes) throw(InvalidHours, InvalidMinutes) {
	if (hours >= 24 || hours < 0)
		throw InvalidHours();
	else if (minutes >= 60 || minutes < 0)
		throw InvalidMinutes();
	return hours * 60 * 60 + minutes * 60;
}

int seconds_noexc(int hours, int minutes) throw() {
	return hours * 60 * 60 + minutes * 60;
}

int main() {
	setlocale(LC_ALL, "");
	int n, h, m;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		try {
			cin >> h >> m;
			cout << seconds_std(h, m) << "\n";
		}
		catch (InvalidHours_std hoursException) {
			cout << hoursException.what() << "\n";
		}
		catch (InvalidMinutes_std minutesException) {
			cout << minutesException.what() << "\n";
		}
	}
	return 0;
}