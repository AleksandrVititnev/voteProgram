#include "MyLib.h"

int main() {
    double number = 0;
    std::cin >> number;
    std::cout << cos(static_cast<double>(number)) << "\n";
    return 0;
}