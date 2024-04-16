#include <iostream>


void callFunc(std::string k) {
    std::string word = "";
    for (auto x : k) {
        if (x == ' ') {
            std::cout << word << "\n";
            word = "";
        } else {
            word = word + x;
        }
    }
    std::cout << word << "\n";
}


int main() {
    std::string k = "khushi agrawal's nvidia interview";
    callFunc(k);
    return 0;
}
