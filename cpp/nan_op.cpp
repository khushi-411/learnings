// https://en.cppreference.com/w/cpp/language/operators
// https://stackoverflow.com/questions/7729646/
// https://stackoverflow.com/questions/1675351/
// https://stackoverflow.com/questions/14047191/

#include <iostream>
#include <cmath>

#define __device__
#define __forceinline__

template <typename acc_t>
struct MaxNanFunctor {
    __device__ __forceinline__ acc_t operator() (acc_t a, acc_t b) const {
        return (std::isnan(a) || a < b) ? b : a;
    }
};

int main() {
    MaxNanFunctor<double> max_functor;  // Create an instance of MaxNanFunctor with double as the template parameter.
    double a = 1.0, b = NAN;
    double max_val = max_functor(a, b);  // Compute the maximum of a and b using the max_functor instance.
    std::cout << "The maximum of " << a << " and " << b << " is " << max_val << std::endl;
    return 0;
}
