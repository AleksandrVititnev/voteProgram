/* figure: abs.cpp */
/*********************/
/* Filename: abs.cpp */
/* Date: 13/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

double abs(const double& number) {
    return (number >= 0 ? number : -number);
}