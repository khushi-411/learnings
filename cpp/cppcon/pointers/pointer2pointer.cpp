#include <iostream>

int main() {
    int x = 7;
    int *px = &x;  // pointer to int
    int **p_px = &px;  // pointer to integer pointer

    **p_px = 77;
    std::cout << "x value: " << x << std::endl;
    std::cout << "*px: " << *px << std::endl;
    std::cout << "**p_px: " << **p_px << std::endl;
    std::cout << "*p_px: " << *p_px << std::endl;
    std::cout << "&x: " << &x << std::endl;
    std::cout << "p_px: " << p_px << std::endl;
    std::cout << "&px: " << &px << std::endl;

    return 0;
}
