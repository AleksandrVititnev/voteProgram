/* figure: pow.cpp */
/*********************/
/* Filename: pow.cpp */
/* Date: 13/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

double pow(const double& number, const int& step) {
    double ans = number;
    for (int x = 1; x < step; x++)
        ans *= number;

    return ans;
}