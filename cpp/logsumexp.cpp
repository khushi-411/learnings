// ref_1 : https://stackoverflow.com/questions/24621954
// ref_2 : https://stackoverflow.com/questions/21926678
// ref_3 : https://stackoverflow.com/questions/28987495
// ref_4 : https://stackoverflow.com/questions/20163469
// ref_5 : https://stackoverflow.com/questions/321068
// ref_6 : https://stackoverflow.com/questions/33434606
// ref_7 : https://stackoverflow.com/questions/15365860

#include <iostream>
#include <cmath>
#include <numeric>
#include <tuple>

template <typename T>
T _sign(T a) {
    return (a < 0) ? -1 : 1;
}

template <typename T>
T _log(T a) {
    return std::log(a);
}

// We can also use:
// 1. auto
// 2. std::tuple
// 3. tie
// TODO: performance benchmark
// IMP: std::pair (otherwise: https://godbolt.org/z/j4qh3h6bo)
template <typename T>
std::pair<T, T> _post_map(T a, T* y, T* sgn) {
    *sgn = _sign(a);
    a *= *sgn;
    *y = _log(a);
    // std::cout << "*sgn : " << *sgn << std::endl;
    // std::cout << "*y : " << *y << std::endl;
    return std::pair<T, T>(*y, *sgn);
}

// TODO: try setting compiler option -std::c++20

template <typename T>
std::pair<T, T> _logsumexp(T* x1) {
    T _exp[5];
    // TODO: Initialize using decltype!
    // decltype(x1) a = { 0 };
    T a = 0;
    for (int i = 0; i < 5; i++) {
        _exp[i] = std::exp(x1[i]);
        // std::cout << _exp[i] << std::endl;
        a += _exp[i];
        // std::cout << "a : " << a << std::endl;
    }
    T y;
    T sgn;
    return _post_map(a, &y, &sgn);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    // std::cout << typeid(arr[1]).name();
    _logsumexp(arr);
    return 0;
}
