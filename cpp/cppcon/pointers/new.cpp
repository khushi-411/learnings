#include <iostream>

int main() {
    int *intArray = new int[3];  // example of heap memory
    delete[] intArray;  // there will be garbage value after deleting
    return 0;
}
