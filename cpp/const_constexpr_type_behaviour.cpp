// ref: https://stackoverflow.com/questions/45593044

#include <iostream>

constexpr double sq_expr(double x) { 
    return x * x; 
}

int main() {
    const double test = 5;   // try with int! It will work.
    constexpr double result = sq_expr((double)test);
    std::cout << result;
    return 0;
}
