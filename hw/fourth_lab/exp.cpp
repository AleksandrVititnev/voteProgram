/* figure: exp.cpp */
/*********************/
/* Filename: exp.cpp */
/* Date: 13/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

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