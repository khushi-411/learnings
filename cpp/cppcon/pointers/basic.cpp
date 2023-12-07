#include <iostream>

int main() {
    int x = 7;
    int* px = &x;  // pointer: variable that stores the memory address of a specific object type

    std::cout << "x: " << x << std::endl;
    std::cout << "px: " << *px /* dereferencing pointer */ << std::endl;

    return 0;
}
