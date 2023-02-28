#include <iostream>
#include <cmath>


template<class _Tp> class complex;

template<class _Tp>
class complex
{
public:
    typedef _Tp value_type;
private:
    value_type __re_;
    value_type __im_;
public:
    constexpr
    complex(const value_type& __re = value_type(), const value_type& __im = value_type())
        : __re_(__re), __im_(__im) {}
    template<class _Xp> constexpr
    complex(const complex<_Xp>& __c)
        : __re_(__c.real()), __im_(__c.imag()) {}
    
    constexpr value_type real() const {return __re_;}
    constexpr value_type imag() const {return __im_;}

    void real(value_type __re) {__re_ = __re;}
    void imag(value_type __im) {__im_ = __im;}

    complex& operator= (const value_type& __re)
        {__re_ = __re; __im_ = value_type(); return *this;}
    complex& operator+=(const value_type& __re) {__re_ += __re; return *this;}
    complex& operator-=(const value_type& __re) {__re_ -= __re; return *this;}
    complex& operator*= (const value_type& __re) {__re_ *= __re; __im_ *= __re; return *this;}
    complex& operator/=(const value_type& __re) {__re_ /= __re; __im_ /= __re; return *this;}

    template<class _Xp> complex& operator= (const complex<_Xp>& __c)
    {
        __re_ = __c.real();
        __im_ = __c.imag();
        return *this;
    }
    template<class _Xp> complex& operator+= (const complex<_Xp>& __c)
    {
        __re_ += __c.real();
        __im_ += __c.imag();
        return *this;
    }
    template<class _Xp> complex& operator-= (const complex<_Xp>& __c)
    {
        __re_ -= __c.real();
        __im_ -= __c.imag();
        return *this;
    }
    template<class _Xp> complex& operator*= (const complex<_Xp>& __c)
    {
        *this = *this * complex(__c.real(), __c.imag());
        return *this;
    }
    template<class _Xp> complex& operator/= (const complex<_Xp>& __c)
    {
        *this = *this / complex(__c.real(), __c.imag());
        return *this;
    }
};

template<class _Tp>
inline
complex<_Tp>
operator+(const complex<_Tp>& __x, const complex<_Tp>& __y)
{
    complex<_Tp> __t(__x);
    __t += __y;
    return __t;
}

template<class _Tp>
inline
complex<_Tp>
operator+(const complex<_Tp>& __x, const _Tp& __y)
{
    complex<_Tp> __t(__x);
    __t += __y;
    return __t;
}

template<class _Tp>
inline
complex<_Tp>
operator+(const _Tp& __x, const complex<_Tp>& __y)
{
    complex<_Tp> __t(__x);
    __t += __y;
    return __t;
}

template<class _Tp>
inline
complex<_Tp>
operator-(const complex<_Tp>& __x, const complex<_Tp>& __y)
{
    complex<_Tp> __t(__x);
    __t -= __y;
    return __t;
}

template<class _Tp>
inline
complex<_Tp>
operator-(const complex<_Tp>& __x, const _Tp& __y)
{
    complex<_Tp> __t(__x);
    __t -= __y;
    return __t;
}

template<class _Tp>
inline
complex<_Tp>
operator-(const _Tp& __x, const complex<_Tp>& __y)
{
    complex<_Tp> __t(__x);
    __t -= __y;
    return __t;
}

// TODO: complex * complex multiplication!

template<class _Tp>
inline
complex<_Tp>
operator*(const complex<_Tp>& __x, const _Tp& __y)
{
    complex<_Tp> __t(__x);
    __t *= __y;
    return __t;
}

template<class _Tp>
inline
complex<_Tp>
operator*(const _Tp& __x, const complex<_Tp>& __y)
{
    complex<_Tp> __t(__y);
    __t *= __x;
    return __t;
}

template<class _Tp>
inline
// complex<_Tp>
bool
operator==(const complex<_Tp>& __x, const complex<_Tp>& __y)
{
    return (__x.real() == __y.real() && __x.imag() == __y.imag());
}

template<class _Tp>
inline
// complex<_Tp>
bool
operator==(const complex<_Tp>& __x, const _Tp& __y)
{
    return __x.real() == __y && __x.imag() == 0;
}

template<class _Tp>
inline
// complex<_Tp>
bool
operator==(const _Tp& __x, const complex<_Tp> __y)
{
    return __x == __y.real() && __y.imag() == 0;
}

template<class _Tp>
inline
// complex<_Tp>
bool
operator!=(const complex<_Tp>& __x, const complex<_Tp>& __y)
{
    return !(__x.real() == __y.real() || __x.imag() == __y.imag());
}

template<class _Tp>
inline
// complex<_Tp>
bool
operator!=(const complex<_Tp>& __x, const _Tp& __y)
{
    return !(__x.real() == __y || __x.imag() == 0);
}

template<class _Tp>
inline
// complex<_Tp>
bool
operator!=(const _Tp& __x, const complex<_Tp>& __y)
{
    return !(__x == __y.real() || __y.imag() == 0);
}

int main() {
    complex<float> _x1(1, 2), _x2(3, 4);
    std::cout << _x1.real() + _x2.imag() << "\n";
    std::cout << _x1.real() - _x2.real() << "\n";
    std::cout << _x2.real() * _x2.real() << "\n";
    bool k = _x1 == _x2;
    std::cout << k << "\n";
    bool s = _x1.real() != _x2;
    std::cout << s;
    return 0;
}
