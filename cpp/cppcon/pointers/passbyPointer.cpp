#include <iostream>

void passValue(int x) {
    x = 411;
}

void passPointer(int* ptr) {
    *ptr = 411;
}

int main() {
    int x = 5;
    int y = 6;

    passValue(x);
    std::cout << "x: " << x << std::endl;
    
    passPointer(&y);
    std::cout << "y: " << y << std::endl;

    return 0;
}
