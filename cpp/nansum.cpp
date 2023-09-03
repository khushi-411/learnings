#include <iostream>
#include <cmath>
#include <complex.h>


template <typename T>
T nansum(const T* a) {
    T sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += std::isnan(a[i]) ? 0 : a[i];
        std::cout << sum << " ";
    }
    return sum;
}


template <typename T>
bool isnan(const std::complex<T>& a) {
    return std::isnan(a.real()) || std::isnan(a.imag());
}


template <typename T>
T nansum_complex(const T* a) {
    T sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += isnan(a[i]) ? 0 : a[i];
    }
    return sum;
}


template <typename scalar_t>
struct nansum_complex_struct {
  std::complex<scalar_t> operator()(const std::complex<scalar_t>* a, int size) {
      std::complex<scalar_t> sum = static_cast<scalar_t>(0.);
      for (int i = 0; i < size; i++) {
        sum += isnan(a[i]) ? static_cast<scalar_t>(0.) : a[i];
      }
      return sum;
  }
};


int main() {
    float a[] = {1., 2., 3., 4., std::sqrt(-1)};
    float result = nansum(a);
    std::cout << result << std::endl;
    
    std::complex <float> b[] = {{1, 2}, {3, 4}, {5, 6}};
    std::complex res = nansum_complex(b);
    std::cout << res << std::endl;

    int size = sizeof(b) / sizeof(b[0]);
    std::complex<float> res1 = nansum_complex_struct<float>()(b, size);
    std::cout << res1;
    return 0;
}
