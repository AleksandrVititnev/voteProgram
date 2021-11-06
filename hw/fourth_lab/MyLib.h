template <typename T>
T pow(T number, int step) {
    T ans = number;
    for (int x = 1; x < step; x++)
        ans *= number;

    return ans;
}

int fact(int number) {
    int ans;
    if (number <= 0) ans = 0;
    else {
        ans = 1;
        for (int x = 2; x <= number; x++)
            ans *= x;
    }
    return ans;
}

template <typename T>
T abs(T number) {
    return (number > 0 ? number : -number);
}

template <typename T>
double sin(T number) {
    double x = static_cast<double>(number);
    const double eps = 1e-15;
    double s = 0;
    double r = x;
    int n = 1;
    while (abs(r) > eps) {
        s += r;
        n = n + 2;
        r = -r * x * x / (n * (n - 1));
    }
    return s;
}

template <typename T>
double cos(T number) {
    double x = static_cast<double>(number);
    const double eps = 1e-15;
    double s = 0;
    double r = 1;
    int n = 0;
    while (abs(r) > eps) {
        s += r;
        n = n + 2;
        r = -r * x * x / (n * (n - 1));
    }
    return s;
}

template <typename T>
double ln(T number) {
    double z = static_cast<double>(number);
    double x = (z - 1) / (z + 1);
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