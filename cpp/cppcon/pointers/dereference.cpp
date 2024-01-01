#include <iostream>

int main() {
    int x = 7;
    int *px = &x;

    std::cout << "x value: " << x << std::endl;
    std::cout << "x address: " << &x << std::endl;
    std::cout << "px points to: " << px << std::endl;
    std::cout << "px dereferenced: " << *px << std::endl;

    return 0;
}
