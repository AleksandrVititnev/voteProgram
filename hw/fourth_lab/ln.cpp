/* figure: ln.cpp */
/*********************/
/* Filename: ln.cpp */
/* Date: 13/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

double ln(const double& number) {
    double x = (number - 1) / (number + 1);
    double s = 0;
    int n = 1;
    for (int i = 0; i < 5; i++) {
        s += pow(x, n) / n;
        n += 2;
    }
    return 2 * s;
}