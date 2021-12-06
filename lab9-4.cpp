#include "Rand.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    int size;
    cout << "Введите количество пар в массиве: ";
    cin >> size;
    Rand random(size);
    cout << "Введите массив пар: "; cin >> random;
    cout << "Массив пар: " << random << "\n\n";


    cout << "1. Выполнить присваивание массивов.\n";
    cout << "2. Вычислить математическое ожидание и дисперсию.\n";
    cout << "3. Вычислить интеграл.\n";
    cout << "0. Выход.\n\n";

    int code;
    while ((cin >> code) && code != 0)
    {
        switch (code)
        {
        case 1:
        {
            int tempsize;
            cout << "Введите количество пар в новом массиве: ";
            cin >> tempsize;
            Rand temp(tempsize);
            cout << "Введите массив пар: "; cin >> temp;
            try {
                random = temp;
                cout << "Массив пар: " << random << "\n";
            }
            catch (std::exception error) {
                std::cout << "Ошибка: " << error.what() << "! Исходный массив не изменен!\n";
            }

            break;
        }
        case 2:
            try
            {
                cout << "Математическое ожидание: " << random.getMathematicalExpectation() << "\n";
                cout << "Дисперсия: " << random.getVariance() << "\n";
            }
            catch (std::exception error) { std::cout << "Ошибка: " << error.what() << ". Измените массив пар!\n"; }
            break;
        case 3: cout << "Значение интеграла: " << Rand::integral() << "\n";
            break;
        case 0: return 0;
        default:
            cout << "Введен неверный код!\n";
            break;
        }
        std::cout << "\n";

    }
}

