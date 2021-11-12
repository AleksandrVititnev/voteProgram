/* figure: MyLib.h */
/*********************/
/* Filename: MyLib.h */
/* Date: 8/11/2021     */
/* Author: Aleksandr Vititnev */
#ifndef MYLIB_H
#define MYLIB_H
#include <iostream>
#include <iomanip>

double pow(const double& number, const int& step);
double abs(const double& number);
double sin(const double& number);
double cos(const double& number);
double ln(const double& number);
double exp(const double& number);

int fact(const int& number);

double calcXY(const double& x, const double& y);

#endif //MYLIB_H
