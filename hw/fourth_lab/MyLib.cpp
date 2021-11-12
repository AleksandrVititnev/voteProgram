#include "MyLib.h"

double pow(const double& number, const int& step) {
    double ans = number;
    for (int x = 1; x < step; x++)
        ans *= number;

    return ans;
}

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

double abs(const double& number) {
    return (number > 0 ? number : -number);
}

double sin(const double& number) {
    const double eps = 1e-15;
    double s = 0;
    double r = number;
    int n = 1;
    while (abs(r) > eps) {
        s += r;
        n = n + 2;
        r = -r * number * number / (n * (n - 1));
    }
    return s;
}

double cos(const double& number) {
    const double eps = 1e-15;
    double s = 0;
    double r = 1;
    int n = 0;
    while (abs(r) > eps) {
        s += r;
        n = n + 2;
        r = -r * number * number / (n * (n - 1));
    }
    return s;
}

double ln(const double& number) {
    double x = (number - 1) / (number + 1);
    double r = x;
    double s = 0;
    int n = 1;
    for (int i = 0; i < 5; i++) {
        s += pow(x, n) / n;
        n += 2;
    }
    return 2 * s;
}

double exp() {
    double x = 1;
    double eps = 1e-15;
    double a = 1;
    double s = 1;
    for (int n = 1; a > eps; n++) {
        a *= x / n;
        s += a;
    }
    return s;
}