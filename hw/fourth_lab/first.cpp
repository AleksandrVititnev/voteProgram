/* figure: first.cpp */
/*********************/
/* Filename: first.cpp */
/* Date: 8/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

int main() {
    char logo[] =
                "*********************************************************\n"
                "* Нижегородский государственный технический университет *\n"
                "* Лабораторная работа 4. Задание 1.                     *\n"
                "* Выполнил студент группы 21-ИВТ-3 Вититнев Александр   *\n"
                "*********************************************************\n";
    bool correct = true;
    double a, b, c, d, hx, hy, x, y;
    int len1, len2;

    std::cout << logo << "\n";

    std::cout << "Введите левую границу первой переменной x: ";
    std::cin >> a;
    std::cout << "Введите правую границу первой переменной x: ";
    std::cin >> b;
    if (a > b) correct = false;

    std::cout << "Введите левую границу первой переменной y: ";
    std::cin >> c;
    std::cout << "Введите правую границу первой переменной y: ";
    std::cin >> d;
    if (c > d) correct = false;

    if (correct) {
        x = a;
        y = c;

        std::cout << "Введите шаг для первой переменной x: ";
        std::cin >> hx;
        
        std::cout << "Введите шаг для первой переменной y: ";
        std::cin >> hy;

        len1 = abs(b - a) / hx + 1;
        len2 = abs(d - c) / hy + 1;

        double** table = new double* [len1];
        for (int x = 0; x < len1; x++) {
            table[x] = new double [len2];

        }

        for (int firstLayer = 0; firstLayer < len1; firstLayer++) {
            for (int secondLayer = 0; secondLayer < len2; secondLayer++) {
                *(*(table + firstLayer) + secondLayer) = 0;
            }
        }

        for (int firstLayer = 0; firstLayer < len1; firstLayer++) {
            std::cout << "X: " << x << "\n";
            for (int secondLayer = 0; secondLayer < len2; secondLayer++) {
                *(*(table + firstLayer) + secondLayer) = calcXY(x, y);
                std::cout << "\t y: " << y << " | F: " << *(*(table + firstLayer) + secondLayer) << "\n";
                y += hy;
            }
            x += hx;
            y = c;
        }

        for (int x = 0; x < len1; x++) {
            delete[] table[x];
        }
        delete[] table;
    }
    return 0;
}