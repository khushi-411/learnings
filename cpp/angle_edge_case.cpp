#include <iostream>
#include <cmath>

#define __host__
#define __device__

template <typename scalar_t>
__host__ __device__ static inline scalar_t angle_wrapper(scalar_t v) {
    if (std::isnan(v)) {
        return v;
    }
    if (std::is_floating_point<scalar_t>::value && v == 0.0) {
        return std::signbit(v) ? M_PI : 0.0;
    }
    return v < 0 ? M_PI : 0;
}

int main() {
    std::cout << angle_wrapper(0) << "\n";
    std::cout << angle_wrapper(-0) << "\n";
    std::cout << angle_wrapper(0.) << "\n";
    std::cout << angle_wrapper(-0.0);
    return 0;
}
