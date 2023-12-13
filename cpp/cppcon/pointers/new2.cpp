#include <iostream>

int main() {
    int *intArray = new int[3];
    for (int i = 0; i < 3; i++) {
	intArray[i] = i;
    }

    int *intArray2 = intArray;
    std::cout << intArray << " should = " << intArray2 << std::endl;

    std::cout << "intArray2[1] = " << intArray2[1] << std::endl;
    delete[] intArray;

    std::cout << "intArray2[1] = " << intArray2[1] << std::endl;  // produces some garbage value
    return 0;
}
