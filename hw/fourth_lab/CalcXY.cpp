#include "MyLib.h"

double calcXY(const double& x, const double& y) {
    double answ = 0;
    double condition = abs(x - y);

    if (condition <= 1) answ = sin(x * (abs(x + y) + 1));
    if (condition > 1 && condition <= 2) answ = ln(abs(x + exp(y)));
    if (condition > 2) answ = 4 * sin(x) + cos(x);

    return answ;
}