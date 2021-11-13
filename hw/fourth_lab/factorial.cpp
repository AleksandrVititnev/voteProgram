/* figure: factorial.cpp */
/*********************/
/* Filename: factorial.cpp */
/* Date: 13/11/2021     */
/* Author: Aleksandr Vititnev */
#include "MyLib.h"

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