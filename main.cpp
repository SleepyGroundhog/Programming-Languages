#include "Array.h"
#include "List.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

template <class C>
void fillContainerByRand(C& container,  size_t size, int key) { srand(key); for (int i = 0; i < size; ++i) container.push_back(rand() % 101 - 50); } // Для Array и List
void fillContainerByRand(double* array, size_t size, int key) { srand(key); for (int i = 0; i < size; ++i) array[i] = (rand() % 101 - 50); }         // Для double*
void print(double* array, size_t size) { for (int i = 0; i < size; ++i) std::cout << array[i] << " "; std::cout << "\n"; }// Функция для вывода double*

template <class I> double findMin(I begin, I end) {
	double minimum = 100;
	I it = begin;
	while (it != end) {
		minimum = std::min(*it, minimum);
		++it;
	}
	return minimum;
}

template <class I> double findSum(I begin, I end) {
	double sum = 0;
	I it = begin;
	while (it != end) {
		sum += *it;
		++it;
	}
	return sum;
}

template <class I> double findAverageByAbs(I begin, I end) {
	double sumabs = 0;
	I it = begin;
	int count;
	for (count = 0; it != end; ++count, ++it)
		sumabs += fabs(*it);
	return sumabs / count;
}

Array<double> processContainer1(double* array, int size) {
	Array<double> modified(size + 2);
	double min = findMin(array, array + size);
	for (int i = 0; i < size; ++i)
		modified.push_back(array[i] * min);
	modified.push_back(findSum(array, array + size));
	modified.push_back(findAverageByAbs(array, array + size));
	return modified;
}


Array<double> processContainer2(double* begin, double* end) {
	Array<double> modified(end - begin + 2);
	double min = findMin(begin, end);
	double* it = begin;
	int i = 0;
	while (it != end) {
		modified.push_back(*it * min);
		++it;
	}
	modified.push_back(findSum(begin, end));
	modified.push_back(findAverageByAbs(begin, end));
	return modified;
}

Array<double> processContainer3(Array<double> array) {
	Array<double> modified(array.size() + 2);
	double min = findMin(array.begin(), array.end());
	for (int i = 0; i < array.size(); ++i)
		modified.push_back(array[i] * min);
	modified.push_back(findSum(array.begin(), array.end()));
	modified.push_back(findAverageByAbs(array.begin(), array.end()));
	return modified;
}


List<double>::Iterator processContainer4(List<double>& list) {
	list.first();
	double min = findMin(list.begin(), list.end());
	double add1 = findSum(list.begin(), list.end()), add2 = findAverageByAbs(list.begin(), list.end());
	for (int i = 0; i < list.size(); ++i, list.next())
		*list.iter() *= min;
	list.push_back(add1);
	list.push_back(add2);
	List<double>::Iterator iter = list.begin();
	return iter;
}

template <class I>
void processContainerIter(I begin, I end) {
	double min = findMin(begin, end);
	
	I iter = begin;
	while (iter != end) {
		(*iter) *= min;
		++iter;
	}
}

int main() {
	setlocale(LC_ALL, "");
	std::cout << "Выберите тип функции для тестирования:\n";
	std::cout << "1. Функция, принимающая обычный массив в качестве аргумента и возвращающая растущий динамический массив.\n";
	std::cout << "2. Функция, принимающая аргументы-указатели на начало и конец обычного массива.\n";
	std::cout << "3. Функция, принимающая растущий динамический массив в качестве аргумента .\n";
	std::cout << "4. Функция, принимающая список в качестве агрумента и возвращаюцая итератор как результат.\n";
	std::cout << "5. Функция, принимающая аргументы-итераторы списка.\n";
	std::cout << "6. Функция, принимающая аргументы-итераторы массива.\n";
	std::cout << "0. Выход\n";

	int code, key;
	size_t size;

	while ((std::cout << "\nВведите код операции: ") && (std::cin >> code) && code != 0) {
		if (code < 1 || code > 6) { std::cout << "Неверный код операции!\n"; continue; }
		std::cout << "Введите длину контейнера и ключ для генератора чисел: ";
		std::cin >> size >> key;
		std::cout << "Сгенерированный контейнер: \n";
		switch (code) {
		case 1:
		{
			double* ctnr1 = new double[size];
			fillContainerByRand(ctnr1, size, key);
			print(ctnr1, size);
			std::cout << "Результирующий контейнер: \n";
			processContainer1(ctnr1, size).print();
			delete[] ctnr1;
			break;
		}
		case 2:
		{
			double* ctnr2 = new double[size + 2];
			fillContainerByRand(ctnr2, size, key);
			print(ctnr2, size);
			std::cout << "Введите смещения a и b для указателей a >= 0, b <= " << size  << ", a < b: ";
			int a, b;
			while ((std::cin >> a >> b) && (a < 0 || b > size || a >= b))
				std::cout << "Некорректное смещение! Введите смещение : ";
			std::cout << "Результирующий контейнер: \n";
			processContainer2(ctnr2 + a, ctnr2 + b).print();
			delete[] ctnr2;
			break;
		}
		case 3:
		{
			Array<double> ctnr3(size);
			fillContainerByRand(ctnr3, size, key);
			ctnr3.print();
			std::cout << "Результирующий контейнер: \n";
			processContainer3(ctnr3).print();
			break;
		}

		case 4:
		{
			List<double> ctnr4;
			fillContainerByRand(ctnr4, size, key);
			ctnr4.print();
			std::cout << "Результирующий контейнер: \n";
			List<double>::Iterator iter = processContainer4(ctnr4);
			while (iter != ctnr4.end()) {
				std::cout << *iter << " ";
				++iter;
			}
			std::cout << "\n";
			break;
		}
		case 5:
		{
			List<double> ctnr5;
			fillContainerByRand(ctnr5, size, key);
			ctnr5.print();
			double add1 = findSum(ctnr5.begin(), ctnr5.end());
			double add2 = findAverageByAbs(ctnr5.begin(), ctnr5.end());
			std::cout << "Введите смещения a и b для итераторов a >= 0, b <= " << size << ", a < b: ";
			int a, b;
			while ((std::cin >> a >> b) && (a < 0 || b > size || a >= b))
				std::cout << "Некорректное смещение! Введите смещение : ";
			std::cout << "Результирующий контейнер: \n";
			processContainerIter(ctnr5.begin() + a, ctnr5.begin() + b);
			ctnr5.push_back(add1);
			ctnr5.push_back(add2);
			ctnr5.print();
			break;
		}
		case 6:
		{
			Array<double> ctnr6;
			fillContainerByRand(ctnr6, size, key);
			ctnr6.print();
			double add1 = findSum(ctnr6.begin(), ctnr6.end());
			double add2 = findAverageByAbs(ctnr6.begin(), ctnr6.end());
			std::cout << "Введите смещения a и b для итераторов a >= 0, b <= " << size << ", a < b: ";
			int a, b;
			while ((std::cin >> a >> b) && (a < 0 || b > size || a >= b))
				std::cout << "Некорректное смещение! Введите смещение : ";
			std::cout << "Результирующий контейнер: \n";
			processContainerIter(ctnr6.begin() + a, ctnr6.begin() + b);
			ctnr6.push_back(add1);
			ctnr6.push_back(add2);
			ctnr6.print();
			break;
		}
		}
	}
	return 0;
}