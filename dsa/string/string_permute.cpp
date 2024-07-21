#include <iostream>


void permute(std::string& k, int l, int r) {
    if (l == r) {
        std::cout << k << "\n";
    } else {
        for (int i = l; i <= r; i++) {
            std::swap(k[l], k[i]);
            permute(k, l + 1, r);
            std::swap(k[l], k[i]);
        }
    }
}


int main() {
    std::string k = "ABC";
    int n = k.size();
    permute(k, 0, n - 1);
    return 0;
}
