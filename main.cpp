#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

class Currency {
public:
	virtual void print() const = 0;
	virtual double inRubles() const = 0;
	
	void setValue(double value) {
		m_value = value;
	}

	void setCourse(double course) {
		m_course = course;
	}

	void read() {
		double a, b;
		cin >> a >> b;
		setValue(a), setCourse(b);
	}

protected:
	double m_value;
	double m_course;

	Currency(double value = 0, double course = 1) : m_value(value), m_course(course) {}

};


class Dollar : public Currency {
public:

	Dollar(double value = 0, double usd = 1) : Currency(value, usd) { }

	void print() const {
		cout << "Dollar " << fixed << setprecision(2) << m_value << " kurs " << m_course << " " << "Rub " << inRubles() << endl;
	}

	double inRubles() const {
		return m_value / m_course;
	}

};

class Euro : public Currency {
public:

	Euro(double value = 0, double eur = 1) : Currency(value, eur) { }

	void print() const {
		cout << "Euro " << fixed << setprecision(2) << m_value << " kurs " << m_course << " " << "Rub " << inRubles() << endl;
	}

	double inRubles() const {
		return m_value / m_course;
	}

};

int main() {
	Euro E;
	Dollar D;
	D.read(), E.read();
	D.print(), E.print();
	int code = 0;
	double temp;
	while (true) {
		cin >> code;
		if (code == 0)
			return 0;
		switch (code)
		{
		case 1: cin >> temp; D.setValue(temp); break;
		case 2: cin >> temp; D.setCourse(temp); break;
		case 3: cin >> temp; E.setValue(temp); break;
		case 4: cin >> temp; E.setCourse(temp); break;
		}
		if (code == 1 || code == 2) D.print();
		else                        E.print();
	}
}