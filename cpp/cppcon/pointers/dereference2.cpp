#include <iostream>

int main() {
    int x = 7;
    int *px = &x;
    *px = 42;
    std::cout << "x value: " << x << std::endl;
    return 0;
}
