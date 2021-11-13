/* figure: cos.cpp */
/*********************/
/* Filename: cos.cpp */
/* Date: 13/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

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