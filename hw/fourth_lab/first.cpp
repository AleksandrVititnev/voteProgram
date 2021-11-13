/* figure: first.cpp */
/*********************/
/* Filename: first.cpp */
/* Date: 8/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

int main() {
    char forSelect = 'u';
    double a, b, c, d, hx, hy, x, y;
    int len1, len2, len3 = 3;
    
    std::ofstream file("out.txt");

    showLogo();

    std::cout << "Здраствуйте, вы хотите ввести данные для вычисления, " 
                << "или нам придумать их самостоятельно?" << "\n" 
                << "Введите: u - пользовательский(по умолчанию), a - автомотический: ";
    std::cin >> forSelect;

    if (!std::cin.good() || (forSelect != 'a' && forSelect != 'u')) {
        forSelect = 'u';
        std::cout << "Выбран вариант по умолчанию: пользовательский ввод.\n";
    }

    if (forSelect == 'u') {
        bool correct = false;
        while (!correct) {
            std::cout << "Введите левую границу первой переменной x: ";
            std::cin >> a;
            std::cout << "Введите правую границу первой переменной x: ";
            std::cin >> b;
            if (a < b)  {
                std::cout << "Введите шаг для первой переменной x: ";
                std::cin >> hx;
                correct = true;
            }
            else std::cout << "Неверно введённые границы: первая < вторая!\n";
        }

        correct = false;
        while (!correct) {
            std::cout << "Введите левую границу первой переменной y: ";
            std::cin >> c;
            std::cout << "Введите правую границу первой переменной y: ";
            std::cin >> d;
            if (c < d)  {
                std::cout << "Введите шаг для первой переменной y: ";
                std::cin >> hy;
                correct = true;
            }
            else std::cout << "Неверно введённые границы: первая < вторая!\n";
        }
    }

    if (forSelect == 'a') {
        bool correct = false;
        srand(time(NULL));
        while (!correct) {
            a = 0.001 * (rand() % 100001);
            b = 0.001 * (rand() % 100001);
            if (b > a) correct = true;
        }
        correct = false;
        while (!correct) {
            c = 0.001 * (rand() % 100001);
            d = 0.001 * (rand() % 100001);
            if (d > c) correct = true;
        }
        hx = 0.001 * (rand() % 1001);
        hy = 0.001 * (rand() % 1001);
    }

    x = a;
    y = c;

    len1 = abs(b - a) / hx + 1;
    len2 = abs(d - c) / hy + 1;

    double*** table = new double** [len1];
    for (int x = 0; x < len1; x++) {
        table[x] = new double* [len2];
    }

    for (int firstLayer = 0; firstLayer < len1; firstLayer++) {
        for (int secondLayer = 0; secondLayer < len2; secondLayer++) {
            table[firstLayer][secondLayer] = new double [len3];
        }
    }

    for (int firstLayer = 0; firstLayer < len1; firstLayer++) {
        for (int secondLayer = 0; secondLayer < len2; secondLayer++) {
            for (int thirdLayer = 0; thirdLayer < len3; thirdLayer++) {
                table[firstLayer][secondLayer][thirdLayer] = 0;
            }
        }
    }

    for (int firstLayer = 0; firstLayer < len1; firstLayer++) {
        std::cout << "X: " << x << "\n";
        for (int secondLayer = 0; secondLayer < len2; secondLayer++) {
            *(*(*(table + firstLayer) + secondLayer) + 0) = x;
            *(*(*(table + firstLayer) + secondLayer) + 1) = y;
            *(*(*(table + firstLayer) + secondLayer) + 2) = calcXY(x, y);
            file << "X: " << table[firstLayer][secondLayer][0] << " | Y: " 
                << table[firstLayer][secondLayer][1] << " | F: " 
                << table[firstLayer][secondLayer][2] << "\n";
            std::cout << "\t y: " << y << " | F: " << table[firstLayer][secondLayer][2] << "\n";
            y += hy;
        }
        x += hx;
        y = c;
    }

    for (int firstLayer = 0; firstLayer < len1; firstLayer++) {
        for (int secondLayer = 0; secondLayer < len2; secondLayer++) {
            delete[] table[firstLayer][secondLayer];
        }
    }
    for (int firstLayer = 0; firstLayer < len1; firstLayer++) {
        delete[] table[firstLayer];
    }
    delete[] table;
    return 0;
}