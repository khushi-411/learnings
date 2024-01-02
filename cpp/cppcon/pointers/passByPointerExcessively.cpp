#include <iostream>

void passByPointerExcessively(int *out, int *in1, int *in2, int *in3) {
    *out = *in1 + *in2 + *in3;
    *in1 = 0;
    *in2 = 0;
    *in3 = 0;
}

int main() {
    int x = 5;
    int y = 6;
    int z = 7;
    int out;

    passByPointerExcessively(&out, &x, &y, &z);
    std::cout << "out: " << out << std::endl;
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "z: " << z << std::endl;

    return 0;
}
