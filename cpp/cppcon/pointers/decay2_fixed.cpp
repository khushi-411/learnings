#include <iostream>
#include <array>

void arrayAsPointerWithSize(short* arr, size_t size) {
    std::cout << "sizeof(arr): " << sizeof(arr) << std::endl;
    for (int i = 0; i < size; i++) {
	std::cout << arr[i] << std::endl;
    }
}

int main() {
    short array[6];
    for (int i = 0; i < 6; i++) {
        array[i] = i;
    }

    std::cout << "sizeof(array): " << sizeof(array) << std::endl;
    arrayAsPointerWithSize(array, 6);

    return 0;
}
