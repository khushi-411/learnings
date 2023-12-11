#include <iostream>
#include <array>

int main() {
    short array[6];
    for (int i = 0; i < 6; i++) {
        array[i] = i;
    }

    short* p_s = &array[2];
    std::cout << "&array[2]: " << *p_s << std::endl;
    p_s = &array[3];
    std::cout << "&array[3]: " << *p_s << std::endl;

    return 0;
}
