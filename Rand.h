#pragma once
#include "Array.h"
#include "cmath"

class Rand {
public:
	using size_t = unsigned int;

	Rand(size_t size) : pairs(size) { }
	Rand(const Rand& rand) : pairs(rand.pairs) { }

	friend std::istream& operator>>(std::istream& inputstream, Rand& rule) {
		inputstream >> rule.pairs;
		return inputstream;
	}

	friend std::ostream& operator<<(std::ostream& outputstream, const Rand& rule) {
		rule.pairs.print(outputstream, ", ");
		return outputstream;
	}

	double getMathematicalExpectation() {
		if (!isFullGroupOfEvents())
			throw invalid_rule("Неверный закон распределения. Сумма вероятностей должна быть равна 1");
		double sum = 0;
		for (auto& element : pairs) {
			sum += element.x * element.p;
		}
		return sum;
	}

	double getVariance() {
		if (!isFullGroupOfEvents())
			throw invalid_rule("Неверный закон распределения. Сумма вероятностей должна быть равна 1");
		Rand pow2(*this);
		for (auto& element : pow2.pairs) {
			element.x = pow(element.x, 2);
		}
		return pow2.getMathematicalExpectation() - pow(getMathematicalExpectation(), 2);
	}

	static double integral() {
		double s = 0, x;
		double i, lim_a, lim_b;
		int n = 1000000;
		srand(1);
		std::cout << "Введите пределы интегрирования для вычисления определенного интеграла: ";
		std::cin >> lim_a >> lim_b;
		double a = 0, b = 0, c = 0;
		std::cout << "Введите агрументы a, b, c для функции f(x) = ax^2+bx+c: ";
		std::cin >> a >> b >> c;	
		for (i = 1; i <= n; i++) {
			x = lim_a + (lim_b - lim_a) * rand() / (1.0 * RAND_MAX);
			s = s + a*x*x+b*x+c;
		}
		return (((lim_b - lim_a) * s) / n);
	}

	bool isFullGroupOfEvents() {
		double sum = 0;
		for (auto& element : pairs) {
			sum += element.p;
		}
		double eps = 0.0000001;
		return (1 - eps < sum && sum < 1 + eps);
	}

	class invalid_rule : public std::logic_error {
	public: invalid_rule(const char* msg) : std::logic_error(msg) {}
	};

private:

	struct Pair {
		double x = 0.0;
		double p = 0.0;

        friend std::istream& operator>>(std::istream& inputstream, Pair& pair) {
            inputstream >> pair.x >> pair.p;
            return inputstream;
        }

        friend std::ostream& operator<<(std::ostream& outputstream, const Pair& pair) {
			outputstream << "(" << pair.x << ";" << pair.p << ")";
            return outputstream;
        }
	};

	Array<Pair> pairs;
};

