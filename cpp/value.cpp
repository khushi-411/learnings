#include <iostream>


namespace ptMgrad {

template <typename T, int size>
class Value {
private:
    typedef T U;
    U x[size];
    U y[size];
public:
    Value() {};

    template <class _X> constexpr
    Value(const Value<_X, size>& _x) {
        std::copy(_x.x, _x.x + size, x);
    }

    template <class _X> constexpr
    Value(const Value<_X, size>& _x, const Value<_X, size>& _y) {
        std::copy(_x.x, _x.x + size, x);
        std::copy(_y.y, _y.y + size, y);
    }

    template <class _X> constexpr
    Value(const _X (&_x)[size]) {
        std::copy(std::begin(_x), std::end(_x), x);
    }

    template <class _X> constexpr
    Value(const _X (&_x)[size], const _X (&_y)[size]) {
        std::copy(std::begin(_x), std::end(_x), x);
        std::copy(std::begin(_y), std::end(_y), y);
    }

    constexpr T operator[](int i) const {
        return x[i];
    }

    constexpr T& operator[](int i) {
        return x[i];
    }

    template <class _X> constexpr
    Value& operator= (const Value<_X, size>& _x) {
        for (size_t i = 0; i < size; i++) {
            x[i] = _x.x[i];
        }
        return *this;
    }

    template <class _X> constexpr
    Value& operator= (const _X& _x) {
        for (size_t i = 0; i < size; i++) {
            x[i] = _x[i];
        }
        return *this;
    }

    template <class _X> constexpr
    Value& operator+= (const Value<_X, size>& _x) {
        for (size_t i = 0; i < size; i++) {
            x[i] += _x.x[i];        }
        return *this;
    }

    template <class _X> constexpr
    Value& operator+= (const _X& _x) {
        for (size_t i = 0; i < size; i++) {
            x[i] += _x[i];
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Value& _x) {
        os << "(";
        for (size_t i = 0; i < size - 1; i++) {
            os << _x.x[i] << ", ";
        }
        os << _x.x[size - 1] << ")";
        return os;
    }

};


template <class T, int size>
inline
Value <T, size>
operator+(const Value<T, size>& _x, const Value<T, size>& _y) {
    Value<T, size> __k;
    for (int i = 0; i < size; i++) {
        __k[i] = _x[i] + _y[i];
    }
    return __k;
}

template <class T, int size>
inline
Value <T, size>
operator+(const Value<T, size>& _x, const T& _y) {
    Value<T, size> __k;
    for (int i = 0; i < size; i++) {
        __k[i] = _x[i] + _y;
    }
    return __k;
}

template <class T, int size>
inline
Value <T, size>
operator+(const T& _x, const Value<T, size>& _y) {
    Value<T, size> __k;
    for (int i = 0; i < size; i++) {
        __k[i] = _x + _y[i];
    }
    return __k;
}

}



int main() {
    double _v1[] = {1.0, 2.0, 3.0};
    double _v2[] = {7.0, 8.0, 9.0};

    ptMgrad::Value<double, 3> v1(_v1);
    ptMgrad::Value<double, 3> v2(_v2);

    ptMgrad::Value<double, 3> v = 2.0 + v1;

    std::cout << v << std::endl;
    return 0;
}
