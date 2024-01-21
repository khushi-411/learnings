#include <iostream>
#include <array>

int main() {
    int *memory = new int [1000];

    // memory leak
    // Tools we can use: address sanitizer or valgrind
    // while (1) {
    //     int *alloc = new int[1];
    // }

    return 0;
}
