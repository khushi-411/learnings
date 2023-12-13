#include <iostream>
#include <cmath>
#include <immintrin.h>
#include <complex>


namespace vec {


template <typename T>
class Vectorized;


template <>
class Vectorized<std::complex<double>> {
private:
    __m256d values;

public:
    using value_type = std::complex<double>;
    using size_type = int;

    Vectorized() {};
    Vectorized(__m256d v) : values(v) {}
    Vectorized(std::complex<double> val) {
        double real_value = val.real();
        double imag_value = val.imag();
        values = _mm256_setr_pd(real_value, imag_value, real_value, imag_value);
    }
    Vectorized(std::complex<double> val1, std::complex<double> val2) {
        values = _mm256_setr_pd(val1.real(), val1.imag(), val2.real(), val2.imag());
    }
    operator __m256d() const {
        return values;
    }

    Vectorized<std::complex<double>> isnan() const {
        __m256d real = _mm256_cmp_pd(values, values, _CMP_UNORD_Q);
        __m256d imag = _mm256_cmp_pd(values, _mm256_permute_pd(values, 0x05), _CMP_UNORD_Q);
        __m256d mask = _mm256_or_pd(real, imag);
        return Vectorized<std::complex<double>>(_mm256_testz_pd(mask, mask));
    }

    friend std::ostream& operator<<(std::ostream& out, const Vectorized<std::complex<double>>& vec) {
        double values[4];
        _mm256_storeu_pd(values, vec.values);
        for (int i = 0; i < 4; i += 2) {
            std::complex<double> val(values[i], values[i + 1]);
            out << "(" << val.real() << "," << val.imag() << ") ";
        }
        return out;
    }

};

}


int main() {
    vec::Vectorized<std::complex<double>> a(std::complex<double>(1, std::nan("")));

    vec::Vectorized<std::complex<double>> c = a.isnan();

    std::cout << c << " ";

    return 0;
}
