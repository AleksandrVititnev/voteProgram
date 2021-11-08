#include <iostream>
#include "MyLib.h"

int main() {
    int x = 10;
    double** table = new double* [x];
    for (int x = 0; x < x; x++) {
        table[x] = new double [x];
    }

    for (int x = 0; x < x; x++) {
        delete[] *(table + x);
    }
    delete[] table;
    return 0;
}