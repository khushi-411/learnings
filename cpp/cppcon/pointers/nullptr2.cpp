#include <iostream>

int main() {
    int *px = nullptr;
    if (nullptr != px) {
        std::cout << *px << std::endl;
    }
    return 0;
}
