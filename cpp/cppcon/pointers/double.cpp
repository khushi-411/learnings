#include <iostream>

// double free occurs when we are sharing data between 2 or more pointers
// the problem is we end up freeing the same memory twice

int main() {
    float *f1 = new float[100];
    float *f2 = f1;
    
    delete[] f2;
    f2 = nullptr;
    delete[] f1;
    f1 = nullptr;
    delete[] f2;
    return 0;
}
