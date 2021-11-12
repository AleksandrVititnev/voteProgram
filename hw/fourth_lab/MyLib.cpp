/* figure: MyLib.cpp */
/*********************/
/* Filename: MyLib.cpp */
/* Date: 8/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"
#define myPi 3.14;

void showLogo() {
    char logo[] =
                "*********************************************************\n"
                "* Нижегородский государственный технический университет *\n"
                "* Лабораторная работа 4. Задание 1.                     *\n"
                "* Выполнил студент группы 21-ИВТ-3 Вититнев Александр   *\n"
                "*********************************************************\n";

    std::cout << logo << "\n";

    return;
}

double getRad() {
    return 360 / 2 / myPi;
}

double pow(const double& number, const int& step) {
    double ans = number;
    for (int x = 1; x < step; x++)
        ans *= number;

    return ans;
}

int fact(const int& number) {
    int ans;
    if (number <= 0) ans = 0;
    else {
        ans = 1;
        for (int x = 2; x <= number; x++)
            ans *= x;
    }
    return ans;
}

double abs(const double& number) {
    return (number >= 0 ? number : -number);
}

double sin(const double& number) {
    double x = number;
    if (number * getRad() > 360) x = x - (static_cast<int>(x * getRad() / 360) * 360) / getRad();
    const double eps = 1e-15;
    double s = 0;
    double r = x;
    int n = 1;
    while (abs(r) > eps) {
        s += r;
        n = n + 2;
        r = -r * x * x / (n * (n - 1));
    }
    return s;
}

double cos(const double& number) {
    double x = number;
    if (number * getRad() > 360) x = x - (static_cast<int>(x * getRad() / 360) * 360) / getRad();
    const double eps = 1e-15;
    double s = 0;
    double r = 1;
    int n = 0;
    while (abs(r) > eps) {
        s += r;
        n = n + 2;
        r = -r * x * x / (n * (n - 1));
    }
    return s;
}

double ln(const double& number) {
    double x = (number - 1) / (number + 1);
    double r = x;
    double s = 0;
    int n = 1;
    for (int i = 0; i < 5; i++) {
        s += pow(x, n) / n;
        n += 2;
    }
    return 2 * s;
}

double exp(const double& number) {
    double eps = 1e-15;
    double a = 1;
    double s = 1;
    for (int n = 1; a > eps; n++) {
        a *= number / n;
        s += a;
    }
    return s;
}