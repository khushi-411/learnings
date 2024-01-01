#include <iostream>
#include <cstdint>

struct UserDefinedType {
    int x, y, z;
    char a, b, c;
};

int main() {
    std::cout << "sizeof(bool): " << sizeof(bool) << std::endl;
    std::cout << "sizeof(unsigned char): " << sizeof(unsigned char) << std::endl;
    std::cout << "sizeof(char): " << sizeof(char) << std::endl;
    std::cout << "sizeof(short): " << sizeof(short) << std::endl;
    std::cout << "sizeof(uint8_t): " << sizeof(uint8_t) << std::endl;
    std::cout << "sizeof(int): " << sizeof(int) << std::endl;
    std::cout << "sizeof(float): " << sizeof(float) << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;
    std::cout << "sizeof(UserDefinedType): " << sizeof(UserDefinedType) << std::endl;
    return 0;
}

