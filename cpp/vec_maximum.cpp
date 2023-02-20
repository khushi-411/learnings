// https://stackoverflow.com/questions/41438493/

#include <iostream>
#include <cmath>
#include <complex.h>

#define __at_align__
#define VECTOR_WIDTH 64

namespace vec {

#if defined(__s390x__)
template <class T, class TEMP=void>
#else
template <class T>
#endif
struct Vectorized{
private:
    __at_align__ T values[VECTOR_WIDTH / sizeof(T)];

public:
    using size_type = int;

    static constexpr size_type size_T = sizeof(T);
    static constexpr size_type size() {
        return VECTOR_WIDTH / size_T;
    }

    // template <class T,
    //          typename std::enable_if<!c10::is_complex<T>::value, int>::type = 0>
    Vectorized<T> inline maximum(const Vectorized<T> &a, const Vectorized<T> &b) const {
        Vectorized<T> c;
        for (int i = 0; i != Vectorized<T>::size(); i++) {
            c[i] = (a[i] > b[i]) ? a[i] : b[i];
            if (std::isnan(a[i])) {
                c[i] = a[i];
            }
        }
        return c;
    }

    T& operator[](int index) {
        return values[index];
    }

    const T& operator[](int index) const {
        return values[index];
    }

};

}

int main() {
    vec::Vectorized<float> a, b, c;
    a[0] = 1.0; a[1] = 2.0; a[2] = 3.0;
    b[0] = 2.0; b[1] = 3.0; b[2] = 1.0;
    c = c.maximum(a, b);
    for (int i = 0; i != c.size(); i++) {
        std::cout << c[i] << " " << i << "\n";
    }
    std::cout << std::endl;
    return 0;
}
