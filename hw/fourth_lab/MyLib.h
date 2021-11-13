/* figure: MyLib.h */
/*********************/
/* Filename: MyLib.h */
/* Date: 8/11/2021     */
/* Author: Aleksandr Vititnev */
#ifndef MYLIB_H
#define MYLIB_H
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#define myPi 3.14;

void showLogo();

double pow(const double& number, const int& step);
int fact(const int& number);
double abs(const double& number);
double getRad();

double sin(const double& number);
double cos(const double& number);
double ln(const double& number);
double exp(const double& number);

double calcXY(const double& x, const double& y);

#endif //MYLIB_H