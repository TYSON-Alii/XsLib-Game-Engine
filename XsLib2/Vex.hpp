#ifndef _XS_VEX2_
#define _XS_VEX2_
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
template <typename T> struct vex2;
template <typename T> struct vex3;
template <typename T> struct vex4;

template <typename T>
struct vex2 {
    T x, y;
    inline operator T* () { return arr(); };
    inline operator T* () const { return arr(); };
    inline operator std::string() const { return (std::to_string(x) + ' ' + std::to_string(y)); };
    inline operator char* () const { return _strdup((std::to_string(x) + ' ' + std::to_string(y)).c_str()); };
#ifdef _XS_STRINX_
    inline operator strinx() const { return strinx(x) + ' ' + strinx(y); };
#endif
#ifdef __VEX2GLM_FUNCS__ // in GLM-Vex.hpp
    __VEX2GLM_FUNCS__;
#undef __VEX2GLM_FUNCS__
#endif
#ifdef __VEX2IM_FUNCS__ // in ImGui-Vex.hpp
    __VEX2IM_FUNCS__;
#undef __VEX2IM_FUNCS__
#endif
    template <int n> T& get();
    template <> constexpr T& get<0>() { return x; };
    template <> constexpr T& get<1>() { return y; };
    inline T* data() { return &x; };
    inline T* data() const { return &x; };
    inline T* arr() const { return new T[2]{ x, y }; };
    inline std::vector<T> vec() const { return { x, y }; };
    inline std::string str(const std::string& sep = " ", const std::string& end = "") const { return std::to_string(x) + sep + std::to_string(y) + end; };
    vex2() = default;
    vex2(const vex2<T>&) = default;
    inline vex2(const T& v) { x = y = v; };
    template <typename _T> inline vex2(_T* v) { x = T(v[0]); y = T(v[1]); };
    template <typename _T> inline vex2(vex2<_T> v) { x = T(v.x); y = T(v.y); };
    template <typename _T> inline vex2(vex3<_T> v) { x = T(v.x); y = T(v.y); };
    template <typename _T> inline vex2(vex4<_T> v) { x = T(v.x); y = T(v.y); };
    template <typename _T1, typename _T2> inline vex2(_T1 v1, _T2 v2) { x = T(v1); y = T(v2); };

    template <typename _T> inline vex2<T>& operator=(_T v) { x = y = T(v); return *this; };
    template <typename _T> inline vex2<T>& operator=(_T* v) { x = T(v[0]); y = T(v[1]); return *this; };
    template <typename _T> inline vex2<T>& operator=(vex2<_T> v) { x = T(v.x); y = T(v.y); return *this; };

    vex2(std::string v);
    vex2(std::string v1, std::string v2);
    vex2<T>& operator=(std::string v);

    inline bool isEmpty() const { return !(x && y); };
    inline operator bool() const { return (x && y); };

    inline vex2<T>& operator~() { x = y = T(); return *this; };
    inline vex2<bool> operator!() const { return vex2<bool>(!x, !y); };
    inline vex2<T>& swap() { *this = vex2<T>(y, x); return *this; };
    inline vex2<T> swap() const { *this = vex2<T>(y, x); return *this; };
    template <typename _T>
    inline vex2<T>& operator,(vex2<_T>& v) {
        const vex2<T> c = *this;
        *this = v;
        v = c;
        return *this;
    };
    inline vex2<T> operator-() const { return vex2<T>(-x, -y); };
    inline vex2<T> operator+() const { return vex2<T>(std::abs(x), std::abs(y)); };
    inline T* operator*() { return &x; };
    inline T* operator*() const { return &x; };

    inline vex2<T> operator()() const { return *this; };
    inline vex2<T> copy() const { return *this; };
    inline vex2<T>& operator()(bool b, const vex2<T>& make) {
        if (b) *this = make;
        return *this;
    };
    inline vex2<T>& operator()(vex2<bool> b, const vex2<T>& make, const bool& _elif = false) {
        if (_elif) {
            if (b.x) x = make.x;
            else if (b.y) y = make.y;
        }
        else {
            if (b.x) x = make.x;
            if (b.y) y = make.y;
        };
        return *this;
    };

    std::vector<T> operator()(std::initializer_list<int> v) {
        std::vector<T> t;
        for (const auto& i : v)
            t.push_back(operator[](i));
        return t;
    };
    std::vector<T> operator()(std::vector<int> v) {
        std::vector<T> t;
        for (const auto& i : v)
            t.push_back(operator[](i));
        return t;
    };
    std::vector<T> operator()(const std::string& v) {
        std::vector<T> t;
        for (const auto& i : v)
            switch (i) {
            case 'x': case 'X':
                t.push_back(x);
                break;
            case 'y': case 'Y':
                t.push_back(y);
                break;
            };
        return t;
    };

    inline T& operator[](const int& v) { return (v % 2) == 0 ? x : y; };
    inline T operator[](const int& v) const { return (v % 2) == 0 ? x : y; };

    template <typename _T> inline vex2<T> operator%(_T v) const { return vex2<T>(std::rand() % int(v), std::rand() % int(v)); };
    template <typename _T> inline vex2<T> operator%(_T* v) const { return vex2<T>(std::rand() % int(v[0]), std::rand() % int(v[1])); };
    template <typename _T> inline vex2<T> operator%(vex2<_T> v) const { return vex2<T>(std::rand() % int(v.x), std::rand() % int(v.y)); };
    template <typename _T> inline vex2<T>& operator%=(_T v) { x = std::rand() % int(v); y = std::rand() % int(v); return *this; }
    template <typename _T> inline vex2<T>& operator%=(_T* v) { x = std::rand() % int(v[0]); y = std::rand() % int(v[1]); return *this; };
    template <typename _T> inline vex2<T>& operator%=(vex2<_T> v) { x = std::rand() % int(v.x); y = std::rand() % int(v.y); return *this; };

    template <typename _T> inline vex2<T> operator|(_T v) const { return std::rand() % 2 == 0 ? vex2<T>(v) : *this; };
    template <typename _T> inline vex2<T> operator|(vex2<_T> v) const { return std::rand() % 2 == 0 ? vex2<T>(v) : *this; };
    template <typename _T> inline vex2<T>& operator|=(vex2<_T> v) { *this = std::rand() % 2 == 0 ? vex2<T>(v) : *this; };
    template <typename _T> inline vex2<T> operator|(vex3<_T> v) const { return std::rand() % 2 == 0 ? vex2<T>(v) : *this; };
    template <typename _T> inline vex2<T>& operator|=(vex3<_T> v) { *this = std::rand() % 2 == 0 ? vex2<T>(v) : *this; };
    template <typename _T> inline vex2<T> operator|(vex4<_T> v) const { return std::rand() % 2 == 0 ? vex2<T>(v) : *this; };
    template <typename _T> inline vex2<T>& operator|=(vex4<_T> v) { *this = std::rand() % 2 == 0 ? vex2<T>(v) : *this; };

    inline vex2<T>& operator++() { x++; y++; return *this; };
    inline vex2<T>& operator--() { x--; y--; return *this; };

    template <typename _T> inline vex2<T>& operator+=(_T v) { x += T(v); y += T(v); return *this; };
    template <typename _T> inline vex2<T>& operator+=(_T* v) { x += T(v[0]); y += T(v[1]); return *this; };
    template <typename _T> inline vex2<T>& operator+=(vex2<_T> v) { x += T(v.x); y += T(v.y); return *this; };
    template <typename _T> inline vex2<T>& operator-=(_T v) { x -= T(v); y -= T(v); return *this; };
    template <typename _T> inline vex2<T>& operator-=(_T* v) { x -= T(v[0]); y -= T(v[1]); return *this; };
    template <typename _T> inline vex2<T>& operator-=(vex2<_T> v) { x -= T(v.x); y -= T(v.y); return *this; };
    template <typename _T> inline vex2<T>& operator*=(_T v) { x *= T(v); y *= T(v); return *this; };
    template <typename _T> inline vex2<T>& operator*=(_T* v) { x *= T(v[0]); y *= T(v[1]); return *this; };
    template <typename _T> inline vex2<T>& operator*=(vex2<_T> v) { x *= T(v.x); y *= T(v.y); return *this; };
    template <typename _T> inline vex2<T>& operator/=(_T v) { x /= T(v); y /= T(v); return *this; };
    template <typename _T> inline vex2<T>& operator/=(_T* v) { x /= T(v[0]); y /= T(v[1]); return *this; };
    template <typename _T> inline vex2<T>& operator/=(vex2<_T> v) { x /= T(v.x); y /= T(v.y); return *this; };
    template <typename _T> inline vex2<T> operator+(_T v) const { return vex2<T>(this->x + T(v), this->y + T(v)); };
    template <typename _T> inline vex2<T> operator+(_T* v) const { return vex2<T>(this->x + T(v[0]), this->y + T(v[1])); };
    template <typename _T> inline vex2<T> operator+(vex2<_T> v) const { return vex2<T>(this->x + T(v.x), this->y + T(v.y)); };
    template <typename _T> inline vex2<T> operator-(_T v) const { return vex2<T>(this->x - T(v), this->y - T(v)); };
    template <typename _T> inline vex2<T> operator-(_T* v) const { return vex2<T>(this->x - T(v[0]), this->y - T(v[1])); };
    template <typename _T> inline vex2<T> operator-(vex2<_T> v) const { return vex2<T>(this->x - T(v.x), this->y - T(v.y)); };
    template <typename _T> inline vex2<T> operator*(_T v) const { return vex2<T>(this->x * T(v), this->y * T(v)); };
    template <typename _T> inline vex2<T> operator*(_T* v) const { return vex2<T>(this->x * T(v[0]), this->y * T(v[1])); };
    template <typename _T> inline vex2<T> operator*(vex2<_T> v) const { return vex2<T>(this->x * T(v.x), this->y * T(v.y)); };
    template <typename _T> inline vex2<T> operator/(_T v) const { return vex2<T>(this->x / T(v), this->y / T(v)); };
    template <typename _T> inline vex2<T> operator/(_T* v) const { return vex2<T>(this->x / T(v[0]), this->y / T(v[1])); };
    template <typename _T> inline vex2<T> operator/(vex2<_T> v) const { return vex2<T>(this->x / T(v.x), this->y / T(v.y)); };
    template <typename _T> inline vex2<T> operator^(_T v) const { return vex2<T>(std::pow(this->x, v), std::pow(this->y, v)); };
    template <typename _T> inline vex2<T> operator^(_T* v) const { return vex2<T>(std::pow(this->x, v[0]), std::pow(this->y, v[1])); };
    template <typename _T> inline vex2<T> operator^(vex2<_T> v) const { return vex2<T>(std::pow(this->x, v.x), std::pow(this->y, v.y)); };

    template <typename _T> inline vex2<bool> operator==(_T v)  const { return vex2<bool>(this->x == T(v), this->y == T(v)); };
    template <typename _T> inline vex2<bool> operator==(_T* v) const { return vex2<bool>(this->x == T(v[0]), this->y == T(v[1])); };
    template <typename _T> inline vex2<bool> operator==(vex2<_T> v) const { return vex2<bool>(this->x == T(v.x), this->y == T(v.y)); };
    template <typename _T> inline vex2<bool> operator!=(_T v)  const { return vex2<bool>(this->x != T(v), this->y != T(v)); };
    template <typename _T> inline vex2<bool> operator!=(_T* v) const { return vex2<bool>(this->x != T(v[0]), this->y != T(v[1])); };
    template <typename _T> inline vex2<bool> operator!=(vex2<_T> v) const { return vex2<bool>(this->x != T(v.x), this->y != T(v.y)); };
    template <typename _T> inline vex2<bool> operator>(_T v)  const { return vex2<bool>(this->x > T(v), this->y > T(v)); };
    template <typename _T> inline vex2<bool> operator>(_T* v) const { return vex2<bool>(this->x > T(v[0]), this->y > T(v[1])); };
    template <typename _T> inline vex2<bool> operator>(vex2<_T> v) const { return vex2<bool>(this->x > T(v.x), this->y > T(v.y)); };
    template <typename _T> inline vex2<bool> operator<(_T v)  const { return vex2<bool>(this->x < T(v), this->y < T(v)); };
    template <typename _T> inline vex2<bool> operator<(_T* v) const { return vex2<bool>(this->x < T(v[0]), this->y < T(v[1])); };
    template <typename _T> inline vex2<bool> operator<(vex2<_T> v) const { return vex2<bool>(this->x < T(v.x), this->y < T(v.y)); };
    template <typename _T> inline vex2<bool> operator>=(_T v)  const { return vex2<bool>(this->x >= T(v), this->y >= T(v)); };
    template <typename _T> inline vex2<bool> operator>=(_T* v) const { return vex2<bool>(this->x >= T(v[0]), this->y >= T(v[1])); };
    template <typename _T> inline vex2<bool> operator>=(vex2<_T> v) const { return vex2<bool>(this->x >= T(v.x), this->y >= T(v.y)); };
    template <typename _T> inline vex2<bool> operator<=(_T v)  const { return vex2<bool>(this->x <= T(v), this->y <= T(v)); };
    template <typename _T> inline vex2<bool> operator<=(_T* v) const { return vex2<bool>(this->x <= T(v[0]), this->y <= T(v[1])); };
    template <typename _T> inline vex2<bool> operator<=(vex2<_T> v) const { return vex2<bool>(this->x <= T(v.x), this->y <= T(v.y)); };

    template <typename _T> inline vex2<T>& operator<<(_T v) { x = v.x; y = v.y; return *this; };
    template <typename _T> inline vex2<T>& operator>>(_T& v) { v.x = x; v.y = y; return *this; };
    template <typename _T> inline const vex2<T>& operator<<(_T v) const { vex2<T> t; t.x = v.x; t.y = v.y; return *this; };
    template <typename _T> inline const vex2<T>& operator>>(_T& v) const { v.x = x; v.y = y; return *this; };

    inline vex2<T>& normalize() { return *this /= (std::abs(x) > std::abs(y) ? std::abs(x) : std::abs(y)); };
    inline vex2<T> normalize() const { return (*this) / (std::abs(x) > std::abs(y) ? std::abs(x) : std::abs(y)); };

    template <typename _T> inline vex2<T>& operator=(vex3<_T> v) { x = T(v.x);  y = T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator+=(vex3<_T> v) { x += T(v.x);  y += T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator-=(vex3<_T> v) { x -= T(v.x);  y -= T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator*=(vex3<_T> v) { x *= T(v.x);  y *= T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator/=(vex3<_T> v) { x /= T(v.x);  y /= T(v.y);    return *this; };
    template <typename _T> inline vex2<T> operator+(vex3<_T> v) const { return vex2<T>(x + T(v.x), y + T(v.y)); };
    template <typename _T> inline vex2<T> operator-(vex3<_T> v) const { return vex2<T>(x - T(v.x), y - T(v.y)); };
    template <typename _T> inline vex2<T> operator*(vex3<_T> v) const { return vex2<T>(x * T(v.x), y * T(v.y)); };
    template <typename _T> inline vex2<T> operator/(vex3<_T> v) const { return vex2<T>(x / T(v.x), y / T(v.y)); };
    template <typename _T> inline vex2<bool> operator==(vex3<_T> v) const { return vex2<bool>(this->x == T(v.x), this->y == T(v.y)); };
    template <typename _T> inline vex2<bool> operator!=(vex3<_T> v) const { return vex2<bool>(this->x != T(v.x), this->y != T(v.y)); };
    template <typename _T> inline vex2<bool> operator>(vex3<_T> v)  const { return vex2<bool>(this->x > T(v.x), this->y > T(v.y)); };
    template <typename _T> inline vex2<bool> operator<(vex3<_T> v)  const { return vex2<bool>(this->x < T(v.x), this->y < T(v.y)); };
    template <typename _T> inline vex2<bool> operator>=(vex3<_T> v) const { return vex2<bool>(this->x >= T(v.x), this->y >= T(v.y)); };
    template <typename _T> inline vex2<bool> operator<=(vex3<_T> v) const { return vex2<bool>(this->x <= T(v.x), this->y <= T(v.y)); };

    template <typename _T> inline vex2<T>& operator=(vex4<_T> v) { x = T(v.x);  y = T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator+=(vex4<_T> v) { x += T(v.x);  y += T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator-=(vex4<_T> v) { x -= T(v.x);  y -= T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator*=(vex4<_T> v) { x *= T(v.x);  y *= T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator/=(vex4<_T> v) { x /= T(v.x);  y /= T(v.y);    return *this; };
    template <typename _T> inline vex2<T>& operator+(vex4<_T> v)  const { return vex2<T>(x + T(v.x), y + T(v.y)); };
    template <typename _T> inline vex2<T>& operator-(vex4<_T> v)  const { return vex2<T>(x - T(v.x), y - T(v.y)); };
    template <typename _T> inline vex2<T>& operator*(vex4<_T> v)  const { return vex2<T>(x * T(v.x), y * T(v.y)); };
    template <typename _T> inline vex2<T>& operator/(vex4<_T> v)  const { return vex2<T>(x / T(v.x), y / T(v.y)); };
    template <typename _T> inline vex2<bool> operator==(vex4<_T> v)  const { return vex2<bool>(this->x == T(v.x), this->y == T(v.y)); };
    template <typename _T> inline vex2<bool> operator!=(vex4<_T> v)  const { return vex2<bool>(this->x != T(v.x), this->y != T(v.y)); };
    template <typename _T> inline vex2<bool> operator>(vex4<_T> v)   const { return vex2<bool>(this->x > T(v.x), this->y > T(v.y)); };
    template <typename _T> inline vex2<bool> operator<(vex4<_T> v)   const { return vex2<bool>(this->x < T(v.x), this->y < T(v.y)); };
    template <typename _T> inline vex2<bool> operator>=(vex4<_T> v)  const { return vex2<bool>(this->x >= T(v.x), this->y >= T(v.y)); };
    template <typename _T> inline vex2<bool> operator<=(vex4<_T> v)  const { return vex2<bool>(this->x <= T(v.x), this->y <= T(v.y)); };

    friend std::ostream& operator<<(std::ostream& os, const vex2<T>& v) { os << v.x << ' ' << v.y; return os; };
    friend std::istream& operator>>(std::istream& is, vex2<T>& v) { std::cout << "x: "; is >> v.x; std::cout << "y: "; is >> v.y; return is; };
};

template <typename T>
struct vex3 {
    T x, y, z;
    inline operator T* () { return arr(); };
    inline operator T* () const { return arr(); };
    inline operator std::string() const { return (std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(z)); };
    inline operator char* () const { return _strdup((std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(z)).c_str()); };
#ifdef _XS_STRINX_
    inline operator strinx() const { return strinx(x) + ' ' + strinx(y) + ' ' + strinx(z); };
#endif
#ifdef __VEX3GLM_FUNCS__
    __VEX3GLM_FUNCS__;
#undef __VEX3GLM_FUNCS__
#endif
#ifdef __VEX3IM_FUNCS__
    __VEX3IM_FUNCS__;
#undef __VEX3IM_FUNCS__
#endif
    template <int n> T& get();
    template <> constexpr T& get<0>() { return x; };
    template <> constexpr T& get<1>() { return y; };
    template <> constexpr T& get<2>() { return z; };
    inline T* data() { return &x; };
    inline T* data() const { return &x; };
    inline T* arr() const { return new T[3]{ x, y, z }; };
    inline std::vector<T> vec() const { return { x, y, z }; };
    inline std::string str(const std::string& sep = " ", const std::string& end = "") const { return std::to_string(x) + sep + std::to_string(y) + sep + std::to_string(z) + end; };
    vex3() = default;
    vex3(const vex3<T>&) = default;
    inline vex3(const T& v) { x = y = z = v; };
    template <typename _T> inline vex3(_T* v) { x = T(v[0]); y = T(v[1]); z = T(v[2]); };
    template <typename _T> inline vex3(vex2<_T> v) { x = T(v.x); y = T(v.y); };
    template <typename _T> inline vex3(vex3<_T> v) { x = T(v.x); y = T(v.y); z = T(v.z); };
    template <typename _T> inline vex3(vex4<_T> v) { x = T(v.x); y = T(v.y); z = T(v.z); };
    template <typename _T1, typename _T2> inline vex3(_T1 v1, _T2 v2) { x = T(v1); y = T(v2); };
    template <typename _T1, typename _T2, typename _T3> inline vex3(_T1 v1, _T2 v2, _T3 v3) { x = T(v1); y = T(v2); z = T(v3); };

    template <typename _T1, typename _T2> inline vex3(vex2<_T1> v1_2, _T2 v3) { x = T(v1_2.x); y = T(v1_2.y); z = T(v3); };
    template <typename _T1, typename _T2> inline vex3(_T1 v1, vex2<_T2> v2_3) { x = T(v1); y = T(v2_3.x); z = T(v2_3.y); };

    template <typename _T> inline vex3<T>& operator=(_T v) { x = y = z = T(v); return *this; };
    template <typename _T> inline vex3<T>& operator=(_T* v) { x = T(v[0]); y = T(v[1]); z = T(v[2]); return *this; };
    template <typename _T> inline vex3<T>& operator=(vex3<_T> v) { x = T(v.x); y = T(v.y); z = T(v.z); return *this; };

    vex3(std::string v);
    vex3(std::string v1, std::string v2);
    vex3(std::string v1, std::string v2, std::string v3);
    vex3<T>& operator=(std::string v);

    inline bool isEmpty()  const { return !(x && y && z); };
    inline operator bool() const { return (x && y && z); };

    inline vex3<T>& operator~() { x = y = z = T(); return *this; };
    inline vex3<bool> operator!() const { return vex3<bool>(!x, !y, !z); };
    inline vex3<T>& swap() { *this = vex3<T>(z, y, x); return *this; };
    inline vex3<T> swap() const { return vex3<T>(z, y, x); };

    template <typename _T>
    inline vex3<T>& operator,(vex3<_T>& v) {
        const vex3<T> c = *this;
        *this = v;
        v = c;
        return *this;
    };
    inline vex3<T> operator-() const { return vex3<T>(-x, -y, -z); };
    inline vex3<T> operator+() const { return vex3<T>(std::abs(x), std::abs(y), std::abs(z)); };
    inline T* operator*() { return &x; };
    inline T* operator*() const { return &x; };

    inline vex3<T> operator()() const { return *this; };
    inline vex3<T> copy() const { return *this; };
    inline vex3<T>& operator()(bool b, const vex3<T>& make) {
        if (b) *this = make;
        return *this;
    };
    inline vex3<T>& operator()(vex2<bool> b, const vex3<T>& make, const bool& _elif = false) {
        if (_elif) {
            if (b.x) x = make.x;
            else if (b.y) y = make.y;
        }
        else {
            if (b.x) x = make.x;
            if (b.y) y = make.y;
        };
        return *this;
    };
    inline vex3<T>& operator()(vex3<bool> b, const vex3<T>& make, const bool& _elif = false) {
        if (_elif) {
            if (b.x) x = make.x;
            else if (b.y) y = make.y;
            else if (b.z) z = make.z;
        }
        else {
            if (b.x) x = make.x;
            if (b.y) y = make.y;
            if (b.z) z = make.z;
        };
        return *this;
    };
    std::vector<T> operator()(std::initializer_list<int> v) {
        std::vector<T> t;
        for (const auto& i : v)
            t.push_back(operator[](i));
        return t;
    };
    std::vector<T> operator()(std::vector<int> v) {
        std::vector<T> t;
        for (const auto& i : v)
            t.push_back(operator[](i));
        return t;
    };
    std::vector<T> operator()(const std::string& v) {
        std::vector<T> t;
        for (const auto& i : v)
            switch (i) {
            case 'x': case 'X':
                t.push_back(x);
                break;
            case 'y': case 'Y':
                t.push_back(y);
                break;
            case 'z': case 'Z':
                t.push_back(z);
                break;
            };
        return t;
    };

    inline T& operator[](const int& v) { return (v % 3) == 0 ? x : (v % 3) == 1 ? y : z; };
    inline T operator[](const int& v) const { return (v % 3) == 0 ? x : (v % 3) == 1 ? y : z; };

    template <typename _T> inline vex3<T> operator%(_T v) const { return vex3<T>(std::rand() % int(v), std::rand() % int(v), std::rand() % int(v)); };
    template <typename _T> inline vex3<T> operator%(_T* v) const { return vex3<T>(std::rand() % int(v[1]), std::rand() % int(v[2]), std::rand() % int(v[3])); };
    template <typename _T> inline vex3<T> operator%(vex3<_T> v) const { return vex3<T>(std::rand() % int(v.x), std::rand() % int(v.y), std::rand() % int(v.z)); };
    template <typename _T> inline vex3<T>& operator%=(_T v) { x = std::rand() % int(v); y = std::rand() % int(v); z = std::rand() % int(v); return *this; };
    template <typename _T> inline vex3<T>& operator%=(_T* v) { x = std::rand() % int(v[0]); y = std::rand() % int(v[1]); z = std::rand() % int(v[2]); return *this; };
    template <typename _T> inline vex3<T>& operator%=(vex3<_T> v) { x = std::rand() % int(v.x); y = std::rand() % int(v.y); z = std::rand() % int(v.z); return *this; };

    template <typename _T> inline vex3<T> operator|(_T v) const { return std::rand() % 2 == 0 ? vex3<T>(v) : *this; };
    template <typename _T> inline vex3<T> operator|(vex3<_T> v) const { return std::rand() % 2 == 0 ? vex3<T>(v) : *this; };
    template <typename _T> inline vex3<T>& operator|=(vex3<_T> v) { *this = std::rand() % 2 == 0 ? vex3<T>(v) : *this; };
    template <typename _T> inline vex3<T> operator|(vex2<_T> v) const { return std::rand() % 2 == 0 ? vex3<T>(v) : *this; };
    template <typename _T> inline vex3<T>& operator|=(vex2<_T> v) { *this = std::rand() % 2 == 0 ? vex3<T>(v) : *this; };
    template <typename _T> inline vex3<T> operator|(vex4<_T> v) const { return std::rand() % 2 == 0 ? vex3<T>(v) : *this; };
    template <typename _T> inline vex3<T>& operator|=(vex4<_T> v) { *this = std::rand() % 2 == 0 ? vex3<T>(v) : *this; };

    inline vex3<T>& operator++() { x++; y++; z++; return *this; };
    inline vex3<T>& operator--() { x--; y--; z--; return *this; };

    template <typename _T> inline vex3<T>& operator+=(_T v) { x += T(v); y += T(v); z += T(v); return *this; };
    template <typename _T> inline vex3<T>& operator+=(_T* v) { x += T(v[0]); y += T(v[1]); z += T(v[2]); return *this; };
    template <typename _T> inline vex3<T>& operator+=(vex3<_T> v) { x += T(v.x); y += T(v.y); z += T(v.z); return *this; };
    template <typename _T> inline vex3<T>& operator-=(_T v) { x -= T(v); y -= T(v); z -= T(v); return *this; };
    template <typename _T> inline vex3<T>& operator-=(_T* v) { x -= T(v[0]); y -= T(v[1]); z -= T(v[2]); return *this; };
    template <typename _T> inline vex3<T>& operator-=(vex3<_T> v) { x -= T(v.x); y -= T(v.y); z -= T(v.z); return *this; };
    template <typename _T> inline vex3<T>& operator*=(_T v) { x *= T(v); y *= T(v); z *= T(v); return *this; };
    template <typename _T> inline vex3<T>& operator*=(_T* v) { x *= T(v[0]); y *= T(v[1]); z *= T(v[2]); return *this; };
    template <typename _T> inline vex3<T>& operator*=(vex3<_T> v) { x *= T(v.x); y *= T(v.y); z *= T(v.z); return *this; };
    template <typename _T> inline vex3<T>& operator/=(_T v) { x /= T(v); y /= T(v); z /= T(v); return *this; };
    template <typename _T> inline vex3<T>& operator/=(_T* v) { x /= T(v[0]); y /= T(v[1]); z /= T(v[2]); return *this; };
    template <typename _T> inline vex3<T>& operator/=(vex3<_T> v) { x /= T(v.x); y /= T(v.y); z /= T(v.z); return *this; };
    template <typename _T> inline vex3<T> operator+(_T v) const { return vex3<T>(this->x + T(v), this->y + T(v), this->z + T(v)); };
    template <typename _T> inline vex3<T> operator+(_T* v) const { return vex3<T>(this->x + T(v[0]), this->y + T(v[1]), this->z + T(v[2])); };
    template <typename _T> inline vex3<T> operator+(vex3<_T> v) const { return vex3<T>(this->x + T(v.x), this->y + T(v.y), this->z + T(v.z)); };
    template <typename _T> inline vex3<T> operator-(_T v) const { return vex3<T>(this->x - T(v), this->y - T(v), this->z - T(v)); };
    template <typename _T> inline vex3<T> operator-(_T* v) const { return vex3<T>(this->x - T(v[0]), this->y - T(v[1]), this->z - T(v[2])); };
    template <typename _T> inline vex3<T> operator-(vex3<_T> v) const { return vex3<T>(this->x - T(v.x), this->y - T(v.y), this->z - T(v.z)); };
    template <typename _T> inline vex3<T> operator*(_T v) const { return vex3<T>(this->x * T(v), this->y * T(v), this->z * T(v)); };
    template <typename _T> inline vex3<T> operator*(_T* v) const { return vex3<T>(this->x * T(v[0]), this->y * T(v[1]), this->z * T(v[2])); };
    template <typename _T> inline vex3<T> operator*(vex3<_T> v) const { return vex3<T>(this->x * T(v.x), this->y * T(v.y), this->z * T(v.z)); };
    template <typename _T> inline vex3<T> operator/(_T v) const { return vex3<T>(this->x / T(v), this->y / T(v), this->z / T(v)); };
    template <typename _T> inline vex3<T> operator/(_T* v) const { return vex3<T>(this->x / T(v[0]), this->y / T(v[1]), this->z / T(v[2])); };
    template <typename _T> inline vex3<T> operator/(vex3<_T> v) const { return vex3<T>(this->x / T(v.x), this->y / T(v.y), this->z / T(v.z)); };
    template <typename _T> inline vex3<T> operator^(_T v) const { return vex3<T>(std::pow(this->x, v), std::pow(this->y, v), std::pow(this->z, v)); };
    template <typename _T> inline vex3<T> operator^(_T* v) const { return vex3<T>(std::pow(this->x, v[0]), std::pow(this->y, v[1]), std::pow(this->z, v[2])); };
    template <typename _T> inline vex3<T> operator^(vex3<_T> v) const { return vex3<T>(std::pow(this->x, v.x), std::pow(this->y, v.y), std::pow(this->z, v.z)); };

    template <typename _T> inline vex3<bool> operator==(_T v)  const { return vex3<bool>(this->x == T(v), this->y == T(v), this->z == T(v)); };
    template <typename _T> inline vex3<bool> operator==(_T* v) const { return vex3<bool>(this->x == T(v[0]), this->y == T(v[1]), this->z == T(v[2])); };
    template <typename _T> inline vex3<bool> operator==(vex3<_T> v) const { return vex3<bool>(this->x == T(v.x), this->y == T(v.y), this->z == T(v.z)); };
    template <typename _T> inline vex3<bool> operator!=(_T v)  const { return vex3<bool>(this->x != T(v), this->y != T(v), this->z != T(v)); };
    template <typename _T> inline vex3<bool> operator!=(_T* v) const { return vex3<bool>(this->x != T(v[0]), this->y != T(v[1]), this->z != T(v[2])); };
    template <typename _T> inline vex3<bool> operator!=(vex3<_T> v) const { return vex3<bool>(this->x != T(v.x), this->y != T(v.y), this->z != T(v.z)); };
    template <typename _T> inline vex3<bool> operator>(_T v)  const { return vex3<bool>(this->x > T(v), this->y > T(v), this->z > T(v)); };
    template <typename _T> inline vex3<bool> operator>(_T* v) const { return vex3<bool>(this->x > T(v[0]), this->y > T(v[1]), this->z > T(v[2])); };
    template <typename _T> inline vex3<bool> operator>(vex3<_T> v) const { return vex3<bool>(this->x > T(v.x), this->y > T(v.y), this->z > T(v.z)); };
    template <typename _T> inline vex3<bool> operator<(_T v)  const { return vex3<bool>(this->x < T(v), this->y < T(v), this->z < T(v)); };
    template <typename _T> inline vex3<bool> operator<(_T* v) const { return vex3<bool>(this->x < T(v[0]), this->y < T(v[1]), this->z < T(v[2])); };
    template <typename _T> inline vex3<bool> operator<(vex3<_T> v) const { return vex3<bool>(this->x < T(v.x), this->y < T(v.y), this->z < T(v.z)); };
    template <typename _T> inline vex3<bool> operator>=(_T v)  const { return vex3<bool>(this->x >= T(v), this->y >= T(v), this->z >= T(v)); };
    template <typename _T> inline vex3<bool> operator>=(_T* v) const { return vex3<bool>(this->x >= T(v[0]), this->y >= T(v[1]), this->z >= T(v[2])); };
    template <typename _T> inline vex3<bool> operator>=(vex3<_T> v) const { return vex3<bool>(this->x >= T(v.x), this->y >= T(v.y), this->z >= T(v.z)); };
    template <typename _T> inline vex3<bool> operator<=(_T v)  const { return vex3<bool>(this->x <= T(v), this->y <= T(v), this->z <= T(v)); };
    template <typename _T> inline vex3<bool> operator<=(_T* v) const { return vex3<bool>(this->x <= T(v[0]), this->y <= T(v[1]), this->z <= T(v[2])); };
    template <typename _T> inline vex3<bool> operator<=(vex3<_T> v) const { return vex3<bool>(this->x <= T(v.x), this->y <= T(v.y), this->z <= T(v.z)); };

    template <typename _T> inline vex3<T>& operator<<(const _T& v) { x = v.x; y = v.y; z = v.z; return *this; };
    template <typename _T> inline vex3<T>& operator>>(_T& v) { v.x = x; v.y = y; v.z = z; return *this; };
    template <typename _T> inline const vex3<T>& operator<<(const _T& v) const { vex3<T> t; t.x = v.x; t.y = v.y; t.z = v.z; return *this; };
    template <typename _T> inline const vex3<T>& operator>>(_T& v) const { v.x = x; v.y = y; v.z = z; return *this; };

    inline vex3<T>& normalize() { return *this /= (std::abs(x) > std::abs(y) ? std::abs(x) : std::abs(y) > std::abs(z) ? std::abs(y) : std::abs(z)); };
    inline vex3<T> normalize() const { return (*this) / (std::abs(x) > std::abs(y) ? std::abs(x) : std::abs(y) > std::abs(z) ? std::abs(y) : std::abs(z)); };

    template <typename _T> inline vex3<T>& operator=(vex2<_T> v)  { x =  T(v.x);   y = T(v.y);    return *this; };
    template <typename _T> inline vex3<T>& operator+=(vex2<_T> v) { x += T(v.x);  y += T(v.y);    return *this; };
    template <typename _T> inline vex3<T>& operator-=(vex2<_T> v) { x -= T(v.x);  y -= T(v.y);    return *this; };
    template <typename _T> inline vex3<T>& operator*=(vex2<_T> v) { x *= T(v.x);  y *= T(v.y);    return *this; };
    template <typename _T> inline vex3<T>& operator/=(vex2<_T> v) { x /= T(v.x);  y /= T(v.y);    return *this; };
    template <typename _T> inline vex3<T> operator+(vex2<_T> v) const { return vex3<T>(x + T(v.x), y + T(v.y)); };
    template <typename _T> inline vex3<T> operator-(vex2<_T> v) const { return vex3<T>(x - T(v.x), y - T(v.y)); };
    template <typename _T> inline vex3<T> operator*(vex2<_T> v) const { return vex3<T>(x * T(v.x), y * T(v.y)); };
    template <typename _T> inline vex3<T> operator/(vex2<_T> v) const { return vex3<T>(x / T(v.x), y / T(v.y)); };
    template <typename _T> inline vex2<bool> operator==(vex2<_T> v) const { return vex2<bool>(this->x == T(v.x), this->y == T(v.y)); };
    template <typename _T> inline vex2<bool> operator!=(vex2<_T> v) const { return vex2<bool>(this->x != T(v.x), this->y != T(v.y)); };
    template <typename _T> inline vex2<bool> operator>(vex2<_T> v)  const { return vex2<bool>(this->x > T(v.x), this->y > T(v.y)); };
    template <typename _T> inline vex2<bool> operator<(vex2<_T> v)  const { return vex2<bool>(this->x < T(v.x), this->y < T(v.y)); };
    template <typename _T> inline vex2<bool> operator>=(vex2<_T> v) const { return vex2<bool>(this->x >= T(v.x), this->y >= T(v.y)); };
    template <typename _T> inline vex2<bool> operator<=(vex2<_T> v) const { return vex2<bool>(this->x <= T(v.x), this->y <= T(v.y)); };

    template <typename _T> inline vex3<T>& operator=(vex4<_T> v)  { x =  T(v.x);  y =  T(v.y);  z =  T(v.z);  return *this; };
    template <typename _T> inline vex3<T>& operator+=(vex4<_T> v) { x += T(v.x);  y += T(v.y);  z += T(v.z);  return *this; };
    template <typename _T> inline vex3<T>& operator-=(vex4<_T> v) { x -= T(v.x);  y -= T(v.y);  z -= T(v.z);  return *this; };
    template <typename _T> inline vex3<T>& operator*=(vex4<_T> v) { x *= T(v.x);  y *= T(v.y);  z *= T(v.z);  return *this; };
    template <typename _T> inline vex3<T>& operator/=(vex4<_T> v) { x /= T(v.x);  y /= T(v.y);  z /= T(v.z);  return *this; };
    template <typename _T> inline vex3<T>& operator+(vex4<_T> v) const { return vex3<T>(x + T(v.x), y + T(v.y), z + T(v.z)); };
    template <typename _T> inline vex3<T>& operator-(vex4<_T> v) const { return vex3<T>(x - T(v.x), y - T(v.y), z - T(v.z)); };
    template <typename _T> inline vex3<T>& operator*(vex4<_T> v) const { return vex3<T>(x * T(v.x), y * T(v.y), z * T(v.z)); };
    template <typename _T> inline vex3<T>& operator/(vex4<_T> v) const { return vex3<T>(x / T(v.x), y / T(v.y), z / T(v.z)); };
    template <typename _T> inline vex3<bool> operator==(vex4<_T> v) const { return vex3<bool>(this->x == T(v.x), this->y == T(v.y), this->z == T(v.z)); };
    template <typename _T> inline vex3<bool> operator!=(vex4<_T> v) const { return vex3<bool>(this->x != T(v.x), this->y != T(v.y), this->z != T(v.z)); };
    template <typename _T> inline vex3<bool> operator>(vex4<_T> v)  const { return vex3<bool>(this->x > T(v.x), this->y > T(v.y), this->z > T(v.z)); };
    template <typename _T> inline vex3<bool> operator<(vex4<_T> v)  const { return vex3<bool>(this->x < T(v.x), this->y < T(v.y), this->z < T(v.z)); };
    template <typename _T> inline vex3<bool> operator>=(vex4<_T> v) const { return vex3<bool>(this->x >= T(v.x), this->y >= T(v.y), this->z >= T(v.z)); };
    template <typename _T> inline vex3<bool> operator<=(vex4<_T> v) const { return vex3<bool>(this->x <= T(v.x), this->y <= T(v.y), this->z <= T(v.z)); };

    friend std::ostream& operator<<(std::ostream& os, const vex3<T>& v) { os << v.x << ' ' << v.y << ' ' << v.z; return os; };
    friend std::istream& operator>>(std::istream& is, vex3<T>& v) { std::cout << "x: "; is >> v.x; std::cout << "y: "; is >> v.y; std::cout << "z: "; is >> v.z; return is; };
};

template <typename T>
struct vex4 {
    T x, y, z, w;
    inline operator T* () { return arr(); };
    inline operator T* () const { return arr(); };
    inline operator std::string() const { return (std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(z) + ' ' + std::to_string(w)); };
    inline operator const char* () const { return _strdup((std::to_string(x) + ' ' + std::to_string(y) + ' ' + std::to_string(z) + ' ' + std::to_string(w)).c_str()); };
#ifdef _XS_STRINX_
    inline operator strinx() const { return strinx(x) + ' ' + strinx(y) + ' ' + strinx(z) + ' ' + strinx(w); };
#endif
#ifdef __VEX4GLM_FUNCS__
    __VEX4GLM_FUNCS__;
#undef __VEX4GLM_FUNCS__
#endif
#ifdef __VEX4IM_FUNCS__
    __VEX4IM_FUNCS__;
#undef __VEX4IM_FUNCS__
#endif
    template <int n> T& get();
    template <> constexpr T& get<0>() { return x; };
    template <> constexpr T& get<1>() { return y; };
    template <> constexpr T& get<2>() { return z; };
    template <> constexpr T& get<3>() { return w; };
    inline T* data() { return &x; };
    inline T* data() const { return &x; };
    inline T* arr() const { return new T[4]{ x, y, z, w }; };
    inline std::vector<T> vec() const { return { x, y, z, w }; };
    inline std::string str(const std::string& sep = " ", const std::string& end = "") const { return std::to_string(x) + sep + std::to_string(y) + sep + std::to_string(z) + sep + std::to_string(w) + end; };
    vex4() = default;
    vex4(const vex4<T>&) = default;
    inline vex4(const T& v) { x = y = z = w = v; };
    template <typename _T> inline vex4(_T* v) { x = T(v[0]); y = T(v[1]); z = T(v[2]); w = T(v[3]); };
    template <typename _T> inline vex4(vex2<_T> v) { x = T(v.x); y = T(v.y); };
    template <typename _T> inline vex4(vex3<_T> v) { x = T(v.x); y = T(v.y); z = T(v.z); };
    template <typename _T> inline vex4(vex4<_T> v) { x = T(v.x); y = T(v.y); z = T(v.z); w = T(v.w); };
    template <typename _T1, typename _T2> inline vex4(_T1 v1, _T2 v2) { x = T(v1); y = T(v2); };
    template <typename _T1, typename _T2, typename _T3> inline vex4(_T1 v1, _T2 v2, _T3 v3) { x = T(v1); y = T(v2); z = T(v3); };
    template <typename _T1, typename _T2, typename _T3, typename _T4> inline vex4(_T1 v1, _T2 v2, _T3 v3, _T4 v4) { x = T(v1); y = T(v2); z = T(v3); w = T(v4); };

    template <typename _T1, typename _T2> inline vex4(_T1 v1, vex3<_T2> v2_3_4) { x = T(v1); y = T(v2_3_4.x); z = T(v2_3_4.y); w = T(v2_3_4.z); };
    template <typename _T1, typename _T2> inline vex4(vex3<_T1> v1_2_3, _T2 v4) { x = T(v1_2_3.x); y = T(v1_2_3.y); z = T(v1_2_3.z); w = T(v4); };

    template <typename _T1, typename _T2> inline vex4(vex2<_T1> v1_2, _T2 v3) { x = T(v1_2.x); y = T(v1_2.y); z = T(v3); };
    template <typename _T1, typename _T2> inline vex4(_T1 v1, vex2<_T2> v2_3) { x = T(v1); y = T(v2_3.x); z = T(v2_3.y); };
    template <typename _T1, typename _T2> inline vex4(vex2<_T1> v1_2, vex2<_T2> v3_4) { x = T(v1_2.x); y = T(v1_2.y); z = T(v3_4.x); w = T(v3_4.y); };
    template <typename _T1, typename _T2, typename _T3> inline vex4(vex2<_T1> v1_2, _T2 v3, _T3 v4) { x = T(v1_2.x); y = T(v1_2.y); z = T(v3); w = T(v4); };
    template <typename _T1, typename _T2, typename _T3> inline vex4(_T1 v1, vex2<_T2> v2_3, _T3 v4) { x = T(v1); y = T(v2_3.x); z = T(v2_3.y); w = T(v4); };
    template <typename _T1, typename _T2, typename _T3> inline vex4(_T1 v1, _T2 v2, vex2<_T3> v3_4) { x = T(v1); y = T(v2); z = T(v3_4.x); w = T(v3_4.y); };

    template <typename _T> inline vex4<T>& operator=(_T v) { x = y = z = w = T(v); return *this; };
    template <typename _T> inline vex4<T>& operator=(_T* v) { x = T(v[0]); y = T(v[1]); z = T(v[2]); w = T(v[3]); return *this; };
    template <typename _T> inline vex4<T>& operator=(vex4<_T> v) { x = T(v.x); y = T(v.y); z = T(v.z); w = T(v.w); return *this; };

    vex4(std::string v);
    vex4(std::string v1, std::string v2);
    vex4(std::string v1, std::string v2, std::string v3);
    vex4(std::string v1, std::string v2, std::string v3, std::string v4);
    vex4<T>& operator=(std::string v);

    inline bool isEmpty() const { return !(x && y && z && w); };
    inline operator bool() const { return (x && y && z && w); };

    inline vex4<T>& operator~() { x = y = z = w = T(); return *this; };
    inline vex4<bool> operator!() const { return vex4<bool>(!x, !y, !z, !w); };
    inline vex4<T>& swap() { *this = vex4<T>(w, z, y, x); return *this; };
    inline vex4<T> swap() const { return vex4<T>(w, z, y, x); };
    template <typename _T>
    inline vex4<T>& operator,(vex4<_T>& v) {
        const vex4<T> c = *this;
        *this = v;
        v = c;
        return *this;
    };
    inline vex4<T> operator-() const { return vex4<T>(-x, -y, -z, -w); };
    inline vex4<T> operator+() const { return vex4<T>(std::abs(x), std::abs(y), std::abs(z), std::abs(w)); };
    inline T* operator*() { return &x; };
    inline T* operator*() const { return &x; };

    inline vex4<T> operator()() const { return *this; };
    inline vex4<T> copy() const { return *this; };
    inline vex4<T>& operator()(bool b, const vex4<T>& make) {
        if (b) *this = make;
        return *this;
    };
    inline vex4<T>& operator()(vex2<bool> b, const vex4<T>& make, const bool& _elif = false) {
        if (_elif) {
            if (b.x) x = make.x;
            else if (b.y) y = make.y;
        }
        else {
            if (b.x) x = make.x;
            if (b.y) y = make.y;
        };
        return *this;
    };
    inline vex4<T>& operator()(vex3<bool> b, const vex4<T>& make, const bool& _elif = false) {
        if (_elif) {
            if (b.x) x = make.x;
            else if (b.y) y = make.y;
            else if (b.z) z = make.z;
        }
        else {
            if (b.x) x = make.x;
            if (b.y) y = make.y;
            if (b.z) z = make.z;
        };
        return *this;
    };
    inline vex4<T>& operator()(vex4<bool> b, const vex4<T>& make, const bool& _elif = false) {
        if (_elif) {
            if (b.x) x = make.x;
            else if (b.y) y = make.y;
            else if (b.z) z = make.z;
            else if (b.w) w = make.w;
        }
        else {
            if (b.x) x = make.x;
            if (b.y) y = make.y;
            if (b.z) z = make.z;
            if (b.w) w = make.w;
        };
        return *this;
    };
    std::vector<T> operator()(std::initializer_list<int> v) {
        std::vector<T> t;
        for (const auto& i : v)
            t.push_back(operator[](i));
        return t;
    };
    std::vector<T> operator()(std::vector<int> v) {
        std::vector<T> t;
        for (const auto& i : v)
            t.push_back(operator[](i));
        return t;
    };
    std::vector<T> operator()(const std::string& v) {
        std::vector<T> t;
        for (const auto& i : v)
            switch (i) {
            case 'x': case 'X':
                t.push_back(x);
                break;
            case 'y': case 'Y':
                t.push_back(y);
                break;
            case 'z': case 'Z':
                t.push_back(z);
                break;
            case 'w': case 'W':
                t.push_back(w);
                break;
            };
        return t;
    };

    inline T& operator[](const int& v) { return (v % 4) == 0 ? x : (v % 4) == 1 ? y : (v % 4) == 2 ? z : w; };
    inline T operator[](const int& v) const { return (v % 4) == 0 ? x : (v % 4) == 1 ? y : (v % 4) == 2 ? z : w; };

    template <typename _T> inline vex4<T> operator%(_T v) const { return vex4<T>(std::rand() % int(v), std::rand() % int(v), std::rand() % int(v), std::rand() % int(v)); };
    template <typename _T> inline vex4<T> operator%(_T* v) const { return vex4<T>(std::rand() % int(v[0]), std::rand() % int(v[1]), std::rand() % int(v[2]), std::rand() % int(v[3])); };
    template <typename _T> inline vex4<T> operator%(vex4<_T> v) const { return vex4<T>(std::rand() % int(v.x), std::rand() % int(v.y), std::rand() % int(v.z), std::rand() % int(v.w)); };
    template <typename _T> inline vex4<T>& operator%=(_T v) { x = std::rand() % int(v); y = std::rand() % int(v); z = std::rand() % int(v); w = std::rand() % int(v); return *this; };
    template <typename _T> inline vex4<T>& operator%=(_T* v) { x = std::rand() % int(v[0]); y = std::rand() % int(v[1]); z = std::rand() % int(v[2]); w = std::rand() % int(v[3]); return *this; };
    template <typename _T> inline vex4<T>& operator%=(vex4<_T> v) { x = std::rand() % int(v.x); y = std::rand() % int(v.y); z = std::rand() % int(v.z); w = std::rand() % int(v.w); return *this; };

    template <typename _T> inline vex4<T> operator|(_T v) const { return std::rand() % 2 == 0 ? vex4<T>(v) : *this; };
    template <typename _T> inline vex4<T> operator|(vex4<_T> v) const { return std::rand() % 2 == 0 ? vex4<T>(v) : *this; };
    template <typename _T> inline vex4<T>& operator|=(vex4<_T> v) { *this = std::rand() % 2 == 0 ? vex4<T>(v) : *this; };
    template <typename _T> inline vex4<T> operator|(vex3<_T> v) const { return std::rand() % 2 == 0 ? vex4<T>(v) : *this; };
    template <typename _T> inline vex4<T>& operator|=(vex3<_T> v) { *this = std::rand() % 2 == 0 ? vex4<T>(v) : *this; };
    template <typename _T> inline vex4<T> operator|(vex2<_T> v) const { return std::rand() % 2 == 0 ? vex4<T>(v) : *this; };
    template <typename _T> inline vex4<T>& operator|=(vex2<_T> v) { *this = std::rand() % 2 == 0 ? vex4<T>(v) : *this; };

    inline vex4<T>& operator++() { x++; y++; z++; w++; return *this; };
    inline vex4<T>& operator--() { x--; y--; z--; w--; return *this; };

    template <typename _T> inline vex4<T>& operator+=(_T v) { x += T(v); y += T(v); z += T(v); w += T(v); return *this; };
    template <typename _T> inline vex4<T>& operator+=(_T* v) { x += T(v[0]); y += T(v[1]); z += T(v[2]); w += T(v[3]); return *this; };
    template <typename _T> inline vex4<T>& operator+=(vex4<_T> v) { x += T(v.x); y += T(v.y); z += T(v.z); w += T(v.w); return *this; };
    template <typename _T> inline vex4<T>& operator-=(_T v) { x -= T(v); y -= T(v); z -= T(v); w -= T(v); return *this; };
    template <typename _T> inline vex4<T>& operator-=(_T* v) { x -= T(v[0]); y -= T(v[1]); z -= T(v[2]); w -= T(v[3]); return *this; };
    template <typename _T> inline vex4<T>& operator-=(vex4<_T> v) { x -= T(v.x); y -= T(v.y); z -= T(v.z); w -= T(v.w); return *this; };
    template <typename _T> inline vex4<T>& operator*=(_T v) { x *= T(v); y *= T(v); z *= T(v); w *= T(v); return *this; };
    template <typename _T> inline vex4<T>& operator*=(_T* v) { x *= T(v[0]); y *= T(v[1]); z *= T(v[2]); w *= T(v[3]); return *this; };
    template <typename _T> inline vex4<T>& operator*=(vex4<_T> v) { x *= T(v.x); y *= T(v.y); z *= T(v.z); w *= T(v.w); return *this; };
    template <typename _T> inline vex4<T>& operator/=(_T v) { x /= T(v); y /= T(v); z /= T(v); w /= T(v); return *this; };
    template <typename _T> inline vex4<T>& operator/=(_T* v) { x /= T(v[0]); y /= T(v[1]); z /= T(v[2]); w /= T(v[3]); return *this; };
    template <typename _T> inline vex4<T>& operator/=(vex4<_T> v) { x /= T(v.x); y /= T(v.y); z /= T(v.z); w /= T(v.w); return *this; };
    template <typename _T> inline vex4<T> operator+(_T v) const { return vex4<T>(this->x + T(v), this->y + T(v), this->z + T(v), this->w + T(v)); };
    template <typename _T> inline vex4<T> operator+(_T* v) const { return vex4<T>(this->x + T(v[0]), this->y + T(v[1]), this->z + T(v[2]), this->w + T(v[3])); };
    template <typename _T> inline vex4<T> operator+(vex4<_T> v) const { return vex4<T>(this->x + T(v.x), this->y + T(v.y), this->z + T(v.z), this->w + T(v.w)); };
    template <typename _T> inline vex4<T> operator-(_T v) const { return vex4<T>(this->x - T(v), this->y - T(v), this->z - T(v), this->w - T(v)); };
    template <typename _T> inline vex4<T> operator-(_T* v) const { return vex4<T>(this->x - T(v[0]), this->y - T(v[1]), this->z - T(v[2]), this->w - T(v[3])); };
    template <typename _T> inline vex4<T> operator-(vex4<_T> v) const { return vex4<T>(this->x - T(v.x), this->y - T(v.y), this->z - T(v.z), this->w - T(v.w)); };
    template <typename _T> inline vex4<T> operator*(_T v) const { return vex4<T>(this->x * T(v), this->y * T(v), this->z * T(v), this->w * T(v)); };
    template <typename _T> inline vex4<T> operator*(_T* v) const { return vex4<T>(this->x * T(v[0]), this->y * T(v[1]), this->z * T(v[2]), this->w * T(v[3])); };
    template <typename _T> inline vex4<T> operator*(vex4<_T> v) const { return vex4<T>(this->x * T(v.x), this->y * T(v.y), this->z * T(v.z), this->w * T(v.w)); };
    template <typename _T> inline vex4<T> operator/(_T v) const { return vex4<T>(this->x / T(v), this->y / T(v), this->z / T(v), this->w / T(v)); };
    template <typename _T> inline vex4<T> operator/(_T* v) const { return vex4<T>(this->x / T(v[0]), this->y / T(v[1]), this->z / T(v[2]), this->w / T(v[3])); };
    template <typename _T> inline vex4<T> operator/(vex4<_T> v) const { return vex4<T>(this->x / T(v.x), this->y / T(v.y), this->z / T(v.z), this->w / T(v.w)); };
    template <typename _T> inline vex4<T> operator^(_T v) const { return vex4<T>(std::pow(this->x, v), std::pow(this->y, v), std::pow(this->z, v), std::pow(this->w, v)); };
    template <typename _T> inline vex4<T> operator^(_T* v) const { return vex4<T>(std::pow(this->x, v[0]), std::pow(this->y, v[1]), std::pow(this->z, v[2]), std::pow(this->w, v[3])); };
    template <typename _T> inline vex4<T> operator^(vex4<_T> v) const { return vex4<T>(std::pow(this->x, v.x), std::pow(this->y, v.y), std::pow(this->z, v.z), std::pow(this->w, w)); };

    template <typename _T> inline vex4<bool> operator==(_T v)  const { return vex4<bool>(this->x == T(v), this->y == T(v), this->z == T(v), this->w == T(v)); };
    template <typename _T> inline vex4<bool> operator==(_T* v) const { return vex4<bool>(this->x == T(v[0]), this->y == T(v[1]), this->z == T(v[2]), this->w == T(v[3])); };
    template <typename _T> inline vex4<bool> operator==(vex4<_T> v) const { return vex4<bool>(this->x == T(v.x), this->y == T(v.y), this->z == T(v.z), this->w == T(v.w)); };
    template <typename _T> inline vex4<bool> operator!=(_T v)  const { return vex4<bool>(this->x != T(v), this->y != T(v), this->z != T(v), this->w != T(v)); };
    template <typename _T> inline vex4<bool> operator!=(_T* v) const { return vex4<bool>(this->x != T(v[0]), this->y != T(v[1]), this->z != T(v[2]), this->w != T(v[3])); };
    template <typename _T> inline vex4<bool> operator!=(vex4<_T> v) const { return vex4<bool>(this->x != T(v.x), this->y != T(v.y), this->z != T(v.z), this->w != T(v.w)); };
    template <typename _T> inline vex4<bool> operator>(_T v)  const { return vex4<bool>(this->x > T(v), this->y > T(v), this->z > T(v), this->w > T(v)); };
    template <typename _T> inline vex4<bool> operator>(_T* v) const { return vex4<bool>(this->x > T(v[0]), this->y > T(v[1]), this->z > T(v[2]), this->w > T(v[3])); };
    template <typename _T> inline vex4<bool> operator>(vex4<_T> v) const { return vex4<bool>(this->x > T(v.x), this->y > T(v.y), this->z > T(v.z), this->w > T(v.w)); };
    template <typename _T> inline vex4<bool> operator<(_T v)  const { return vex4<bool>(this->x < T(v), this->y < T(v), this->z < T(v), this->w < T(v)); };
    template <typename _T> inline vex4<bool> operator<(_T* v) const { return vex4<bool>(this->x < T(v[0]), this->y < T(v[1]), this->z < T(v[2]), this->w < T(v[3])); };
    template <typename _T> inline vex4<bool> operator<(vex4<_T> v) const { return vex4<bool>(this->x < T(v.x), this->y < T(v.y), this->z < T(v.z), this->w < T(v.w)); };
    template <typename _T> inline vex4<bool> operator>=(_T v)  const { return vex4<bool>(this->x >= T(v), this->y >= T(v), this->z >= T(v), this->w >= T(v)); };
    template <typename _T> inline vex4<bool> operator>=(_T* v) const { return vex4<bool>(this->x >= T(v[0]), this->y >= T(v[1]), this->z >= T(v[2]), this->w >= T(v[3])); };
    template <typename _T> inline vex4<bool> operator>=(vex4<_T> v) const { return vex4<bool>(this->x >= T(v.x), this->y >= T(v.y), this->z >= T(v.z), this->w >= T(v.w)); };
    template <typename _T> inline vex4<bool> operator<=(_T v)  const { return vex4<bool>(this->x <= T(v), this->y <= T(v), this->z <= T(v), this->w <= T(v)); };
    template <typename _T> inline vex4<bool> operator<=(_T* v) const { return vex4<bool>(this->x <= T(v[0]), this->y <= T(v[1]), this->z <= T(v[2]), this->w <= T(v[3])); };
    template <typename _T> inline vex4<bool> operator<=(vex4<_T> v) const { return vex4<bool>(this->x <= T(v.x), this->y <= T(v.y), this->z <= T(v.z), this->w <= T(v.w)); };

    template <typename _T> inline vex4<T>& operator<<(_T v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; };
    template <typename _T> inline vex4<T>& operator>>(_T& v) { v.x = x; v.y = y; v.z = z; v.w = w; return *this; };
    template <typename _T> inline const vex4<T>& operator<<(_T v) const { vex4<T> t; t.x = v.x; t.y = v.y; t.z = v.z; t.w = v.w; return *this; };
    template <typename _T> inline const vex4<T>& operator>>(_T& v) const { v.x = x; v.y = y; v.z = z; v.w = w; return *this; };

    inline vex4<T>& normalize() { return *this /= ((std::abs(x) > std::abs(y) && std::abs(x) > std::abs(z) && std::abs(x) > std::abs(w)) ? std::abs(x) : (std::abs(y) > std::abs(z) && std::abs(y) > std::abs(w)) ? std::abs(y) : (std::abs(z) > std::abs(w)) ? std::abs(z) : std::abs(w)); };
    inline vex4<T> normalize() const { return *this / ((std::abs(x) > std::abs(y) && std::abs(x) > std::abs(z) && std::abs(x) > std::abs(w)) ? std::abs(x) : (std::abs(y) > std::abs(z) && std::abs(y) > std::abs(w)) ? std::abs(y) : (std::abs(z) > std::abs(w)) ? std::abs(z) : std::abs(w)); };

    template <typename _T> inline vex4<T>& operator=(vex2<_T> v) { x = T(v.x);  y = T(v.y);    return *this; };
    template <typename _T> inline vex4<T>& operator+=(vex2<_T> v) { x += T(v.x);  y += T(v.y);    return *this; };
    template <typename _T> inline vex4<T>& operator-=(vex2<_T> v) { x -= T(v.x);  y -= T(v.y);    return *this; };
    template <typename _T> inline vex4<T>& operator*=(vex2<_T> v) { x *= T(v.x);  y *= T(v.y);    return *this; };
    template <typename _T> inline vex4<T>& operator/=(vex2<_T> v) { x /= T(v.x);  y /= T(v.y);    return *this; };
    template <typename _T> inline vex4<T> operator+(vex2<_T> v) const { return vex4<T>(x + T(v.x), y + T(v.y)); };
    template <typename _T> inline vex4<T> operator-(vex2<_T> v) const { return vex4<T>(x - T(v.x), y - T(v.y)); };
    template <typename _T> inline vex4<T> operator*(vex2<_T> v) const { return vex4<T>(x * T(v.x), y * T(v.y)); };
    template <typename _T> inline vex4<T> operator/(vex2<_T> v) const { return vex4<T>(x / T(v.x), y / T(v.y)); };
    template <typename _T> inline vex2<bool> operator==(vex2<_T> v) const { return vex2<bool>(this->x == T(v.x), this->y == T(v.y)); };
    template <typename _T> inline vex2<bool> operator!=(vex2<_T> v) const { return vex2<bool>(this->x != T(v.x), this->y != T(v.y)); };
    template <typename _T> inline vex2<bool> operator>(vex2<_T> v)  const { return vex2<bool>(this->x > T(v.x), this->y > T(v.y)); };
    template <typename _T> inline vex2<bool> operator<(vex2<_T> v)  const { return vex2<bool>(this->x < T(v.x), this->y < T(v.y)); };
    template <typename _T> inline vex2<bool> operator>=(vex2<_T> v) const { return vex2<bool>(this->x >= T(v.x), this->y >= T(v.y)); };
    template <typename _T> inline vex2<bool> operator<=(vex2<_T> v) const { return vex2<bool>(this->x <= T(v.x), this->y <= T(v.y)); };

    template <typename _T> inline vex4<T>& operator=(vex3<_T> v) { x = T(v.x);  y = T(v.y);  z = T(v.z);  return *this; };
    template <typename _T> inline vex4<T>& operator+=(vex3<_T> v) { x += T(v.x);  y += T(v.y);  z += T(v.z);  return *this; };
    template <typename _T> inline vex4<T>& operator-=(vex3<_T> v) { x -= T(v.x);  y -= T(v.y);  z -= T(v.z);  return *this; };
    template <typename _T> inline vex4<T>& operator*=(vex3<_T> v) { x *= T(v.x);  y *= T(v.y);  z *= T(v.z);  return *this; };
    template <typename _T> inline vex4<T>& operator/=(vex3<_T> v) { x /= T(v.x);  y /= T(v.y);  z /= T(v.z);  return *this; };
    template <typename _T> inline vex4<T>& operator+(vex3<_T> v) const { return vex4<T>(x + T(v.x), y + T(v.y), z + T(v.z)); };
    template <typename _T> inline vex4<T>& operator-(vex3<_T> v) const { return vex4<T>(x - T(v.x), y - T(v.y), z - T(v.z)); };
    template <typename _T> inline vex4<T>& operator*(vex3<_T> v) const { return vex4<T>(x * T(v.x), y * T(v.y), z * T(v.z)); };
    template <typename _T> inline vex4<T>& operator/(vex3<_T> v) const { return vex4<T>(x / T(v.x), y / T(v.y), z / T(v.z)); };
    template <typename _T> inline vex3<bool> operator==(vex3<_T> v) const { return vex3<bool>(this->x == T(v.x), this->y == T(v.y), this->z == T(v.z)); };
    template <typename _T> inline vex3<bool> operator!=(vex3<_T> v) const { return vex3<bool>(this->x != T(v.x), this->y != T(v.y), this->z != T(v.z)); };
    template <typename _T> inline vex3<bool> operator>(vex3<_T> v)  const { return vex3<bool>(this->x > T(v.x), this->y > T(v.y), this->z > T(v.z)); };
    template <typename _T> inline vex3<bool> operator<(vex3<_T> v)  const { return vex3<bool>(this->x < T(v.x), this->y < T(v.y), this->z < T(v.z)); };
    template <typename _T> inline vex3<bool> operator>=(vex3<_T> v) const { return vex3<bool>(this->x >= T(v.x), this->y >= T(v.y), this->z >= T(v.z)); };
    template <typename _T> inline vex3<bool> operator<=(vex3<_T> v) const { return vex3<bool>(this->x <= T(v.x), this->y <= T(v.y), this->z <= T(v.z)); };

    friend std::ostream& operator<<(std::ostream& os, const vex4<T>& v) { os << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w; return os; };
    friend std::istream& operator>>(std::istream& is, vex4<T>& v) { std::cout << "x: "; is >> v.x; std::cout << "y: "; is >> v.y; std::cout << "z: "; is >> v.z; std::cout << "w: "; is >> v.w; return is; };
};
typedef vex2<bool>          vex2b;
typedef vex2<float>         vex2f;
typedef vex2<int>           vex2i;
typedef vex2<size_t>        vex2ui;
typedef vex2<double>        vex2d;
typedef vex2<long double>   vex2ld;
typedef vex2<long int>      vex2li;
typedef vex2<long long int> vex2lli;
typedef vex2<unsigned char> vex2ub;
typedef vex2<std::string>   vex2s;

typedef vex3<bool>          vex3b;
typedef vex3<float>         vex3f;
typedef vex3<int>           vex3i;
typedef vex3<size_t>        vex3ui;
typedef vex3<double>        vex3d;
typedef vex3<long double>   vex3ld;
typedef vex3<long int>      vex3li;
typedef vex3<long long int> vex3lli;
typedef vex3<unsigned char> vex3ub;
typedef vex3<std::string>   vex3s;

typedef vex4<bool>          vex4b;
typedef vex4<float>         vex4f;
typedef vex4<int>           vex4i;
typedef vex4<size_t>        vex4ui;
typedef vex4<double>        vex4d;
typedef vex4<long double>   vex4ld;
typedef vex4<long int>      vex4li;
typedef vex4<long long int> vex4lli;
typedef vex4<unsigned char> vex4ub;
typedef vex4<std::string>   vex4s;

#ifndef XS_UTILITY
template <typename T> T sto(const std::string&);
template <> inline int sto<int>(const std::string& _str) { return std::stoi(_str); };
template <> inline float sto<float>(const std::string& _str) { return std::stof(_str); };
template <> inline double sto<double>(const std::string& _str) { return std::stod(_str); };
template <> inline long double sto<long double>(const std::string& _str) { return std::stold(_str); };
template <> inline unsigned sto<unsigned>(const std::string& _str) { return (unsigned)std::stoi(_str); };
template <> inline long sto<long>(const std::string& _str) { return std::stol(_str); };
template <> inline long long sto<long long>(const std::string& _str) { return std::stoll(_str); };
template <> inline unsigned long long sto<unsigned long long>(const std::string& _str) { return std::stoull(_str); };
#endif

#define DelForIntVexs(_type) \
template<> vex2<_type>& vex2<_type>::normalize() = delete;      \
template<> vex2<_type> vex2<_type>::normalize() const = delete; \
template<> vex3<_type>& vex3<_type>::normalize() = delete;      \
template<> vex3<_type> vex3<_type>::normalize() const = delete; \
template<> vex4<_type>& vex4<_type>::normalize() = delete;      \
template<> vex4<_type> vex4<_type>::normalize() const = delete;
DelForIntVexs(int)
DelForIntVexs(size_t)
DelForIntVexs(long int)
DelForIntVexs(long long int)
DelForIntVexs(unsigned char)

#undef DelForIntVexs

#define DelSVexs(_type, _t)                                                        \
template<> template <typename _T> _type _type::operator%(_T v) const = delete;     \
template<> template <typename _T> _type _type::operator%(_T* v) const = delete;    \
template<> template <typename _T> _type& _type::operator%=(_T v) = delete;         \
template<> template <typename _T> _type& _type::operator%=(_T* v) = delete;        \
template<> template <typename _T> _type _type::operator%(_t<_T> v) const = delete; \
template<> template <typename _T> _type& _type::operator%=(_t<_T> v) = delete;     \
template<> template <typename _T> _t<bool> _type::operator<(_T v) const = delete;      \
template<> template <typename _T> _t<bool> _type::operator<(_T* v) const = delete;     \
template<> template <typename _T> _t<bool> _type::operator<(_t<_T> v) const = delete;  \
template<> template <typename _T> _t<bool> _type::operator>(_T v) const = delete;      \
template<> template <typename _T> _t<bool> _type::operator>(_T* v) const = delete;     \
template<> template <typename _T> _t<bool> _type::operator>(_t<_T> v) const = delete;  \
template<> template <typename _T> _t<bool> _type::operator<=(_T v) const = delete;     \
template<> template <typename _T> _t<bool> _type::operator<=(_T* v) const = delete;    \
template<> template <typename _T> _t<bool> _type::operator<=(_t<_T> v) const = delete; \
template<> template <typename _T> _t<bool> _type::operator>=(_T v) const = delete;     \
template<> template <typename _T> _t<bool> _type::operator>=(_T* v) const = delete;    \
template<> template <typename _T> _t<bool> _type::operator>=(_t<_T> v) const = delete; \
template<> template <typename _T> _type _type::operator-(_T v)const = delete;      \
template<> template <typename _T> _type _type::operator-(_T* v)const = delete;     \
template<> template <typename _T> _type _type::operator-(_t<_T> v) const = delete; \
template<> template <typename _T> _type& _type::operator-=(_T v) = delete;         \
template<> template <typename _T> _type& _type::operator-=(_T* v) = delete;        \
template<> template <typename _T> _type& _type::operator-=(_t<_T> v) = delete;     \
template<> template <typename _T> _type _type::operator*(_T v) const = delete;     \
template<> template <typename _T> _type _type::operator*(_T* v) const = delete;    \
template<> template <typename _T> _type _type::operator*(_t<_T> v) const = delete; \
template<> template <typename _T> _type& _type::operator*=(_T v) = delete;         \
template<> template <typename _T> _type& _type::operator*=(_T* v) = delete;        \
template<> template <typename _T> _type& _type::operator*=(_t<_T> v) = delete;     \
template<> template <typename _T> _type _type::operator/(_T v) const = delete;     \
template<> template <typename _T> _type _type::operator/(_T* v) const = delete;    \
template<> template <typename _T> _type _type::operator/(_t<_T> v) const = delete; \
template<> template <typename _T> _type& _type::operator/=(_T v) = delete;         \
template<> template <typename _T> _type& _type::operator/=(_T* v) = delete;        \
template<> template <typename _T> _type& _type::operator/=(_t<_T> v) = delete;     \
template<> _type& _type::operator++() = delete;                                    \
template<> _type& _type::operator--() = delete;                                    \
template<> _type& _type::normalize() = delete;                                     \
template<> _type _type::normalize() const = delete;

DelSVexs(vex2<std::string>, vex2)
DelSVexs(vex3<std::string>, vex3)
DelSVexs(vex4<std::string>, vex4)
DelSVexs(vex2<bool>, vex2)
DelSVexs(vex3<bool>, vex3)
DelSVexs(vex4<bool>, vex4)

#undef DelSVexs

#ifdef _XS_STRINX_
template<> template <typename _T> vex2<strinx> vex2<strinx>::operator%(_T v) const = delete;
template<> template <typename _T> vex2<strinx>& vex2<strinx>::operator%=(_T v) = delete;
template<> template <typename _T> vex2<strinx> vex2<strinx>::operator%(vex2<_T> v) const = delete;
template<> template <typename _T> vex2<strinx>& vex2<strinx>::operator%=(vex2<_T> v) = delete;
template<> template <typename _T> bool vex2<strinx>::operator<(_T v) const = delete;
template<> template <typename _T> bool vex2<strinx>::operator<(vex2<_T> v) const = delete;
template<> template <typename _T> bool vex2<strinx>::operator>(_T v) const = delete;
template<> template <typename _T> bool vex2<strinx>::operator>(vex2<_T> v) const = delete;
template<> template <typename _T> bool vex2<strinx>::operator<=(_T v) const = delete;
template<> template <typename _T> bool vex2<strinx>::operator<=(vex2<_T> v) const = delete;
template<> template <typename _T> bool vex2<strinx>::operator>=(_T v) const = delete;
template<> template <typename _T> bool vex2<strinx>::operator>=(vex2<_T> v) const = delete;
template<> vex2<strinx>& vex2<strinx>::normalize() = delete;
template<> vex2<strinx> vex2<strinx>::normalize() const = delete;
typedef vex2<strinx> vex2x;

template<> template <typename _T> vex3<strinx> vex3<strinx>::operator%(_T v) const = delete;
template<> template <typename _T> vex3<strinx>& vex3<strinx>::operator%=(_T v) = delete;
template<> template <typename _T> vex3<strinx> vex3<strinx>::operator%(vex3<_T> v) const = delete;
template<> template <typename _T> vex3<strinx>& vex3<strinx>::operator%=(vex3<_T> v) = delete;
template<> template <typename _T> bool vex3<strinx>::operator<(_T v) const = delete;
template<> template <typename _T> bool vex3<strinx>::operator<(vex3<_T> v) const = delete;
template<> template <typename _T> bool vex3<strinx>::operator>(_T v) const = delete;
template<> template <typename _T> bool vex3<strinx>::operator>(vex3<_T> v) const = delete;
template<> template <typename _T> bool vex3<strinx>::operator<=(_T v) const = delete;
template<> template <typename _T> bool vex3<strinx>::operator<=(vex3<_T> v) const = delete;
template<> template <typename _T> bool vex3<strinx>::operator>=(_T v) const = delete;
template<> template <typename _T> bool vex3<strinx>::operator>=(vex3<_T> v) const = delete;
template<> vex3<strinx>& vex3<strinx>::normalize() = delete;
template<> vex3<strinx> vex3<strinx>::normalize() const = delete;
typedef vex3<strinx> vex3x;

template<> template <typename _T> vex4<strinx> vex4<strinx>::operator%(_T v) const = delete;
template<> template <typename _T> vex4<strinx>& vex4<strinx>::operator%=(_T v) = delete;
template<> template <typename _T> vex4<strinx> vex4<strinx>::operator%(vex4<_T> v) const = delete;
template<> template <typename _T> vex4<strinx>& vex4<strinx>::operator%=(vex4<_T> v) = delete;
template<> template <typename _T> bool vex4<strinx>::operator<(_T v) const = delete;
template<> template <typename _T> bool vex4<strinx>::operator<(vex4<_T> v) const = delete;
template<> template <typename _T> bool vex4<strinx>::operator>(_T v) const = delete;
template<> template <typename _T> bool vex4<strinx>::operator>(vex4<_T> v) const = delete;
template<> template <typename _T> bool vex4<strinx>::operator<=(_T v) const = delete;
template<> template <typename _T> bool vex4<strinx>::operator<=(vex4<_T> v) const = delete;
template<> template <typename _T> bool vex4<strinx>::operator>=(_T v) const = delete;
template<> template <typename _T> bool vex4<strinx>::operator>=(vex4<_T> v) const = delete;
template<> vex4<strinx>& vex4<strinx>::normalize() = delete;
template<> vex4<strinx> vex4<strinx>::normalize() const = delete;
template<> vex4<strinx> vex4<strinx>::percent(strinx v) const = delete;
template<> vex4<strinx> vex4<strinx>::percent(strinx v1, strinx v2, strinx v3, strinx v4) const = delete;
typedef vex4<strinx> vex4x;
#endif

template<typename T> vex2<T>::vex2(std::string v) { x = y = sto<T>(v); };
template<typename T> vex2<T>::vex2(std::string v1, std::string v2) { x = sto<T>(v1); y = sto<T>(v2); };
template<typename T> vex2<T>& vex2<T>::operator=(std::string v) { x = y = sto<T>(v); return *this; };
template<typename T> vex3<T>::vex3(std::string v) { x = y = z = sto<T>(v); };
template<typename T> vex3<T>::vex3(std::string v1, std::string v2) { x = sto<T>(v1); y = sto<T>(v2); };
template<typename T> vex3<T>::vex3(std::string v1, std::string v2, std::string v3) { x = sto<T>(v1); y = sto<T>(v2); z = sto<T>(v3); };
template<typename T> vex3<T>& vex3<T>::operator=(std::string v) { x = y = z = sto<T>(v); return *this; };
template<typename T> vex4<T>::vex4(std::string v) { x = y = z = w = sto<T>(v); };
template<typename T> vex4<T>::vex4(std::string v1, std::string v2) { x = sto<T>(v1); y = sto<T>(v2); };
template<typename T> vex4<T>::vex4(std::string v1, std::string v2, std::string v3) { x = sto<T>(v1); y = sto<T>(v2); z = sto<T>(v3); };
template<typename T> vex4<T>::vex4(std::string v1, std::string v2, std::string v3, std::string v4) { x = sto<T>(v1); y = sto<T>(v2); z = sto<T>(v3); w = sto<T>(v4); };
template<typename T> vex4<T>& vex4<T>::operator=(std::string v) { x = y = z = w = sto<T>(v); return *this; };

inline vex2f operator""_vex2f(unsigned long long v) { return vex2f(v); };
inline vex2i operator""_vex2i(unsigned long long v) { return vex2i(v); };
inline vex2ui operator""_vex2ui(unsigned long long v) { return vex2ui(v); };
inline vex2d operator""_vex2d(unsigned long long v) { return vex2d(v); };
inline vex2ld operator""_vex2ld(unsigned long long v) { return vex2ld(v); };
inline vex2li operator""_vex2li(unsigned long long v) { return vex2li(v); };
inline vex2lli operator""_vex2lli(unsigned long long v) { return vex2lli(v); };

inline vex3f operator""_vex3f(unsigned long long v) { return vex3f(v); };
inline vex3i operator""_vex3i(unsigned long long v) { return vex3i(v); };
inline vex3ui operator""_vex3ui(unsigned long long v) { return vex3ui(v); };
inline vex3d operator""_vex3d(unsigned long long v) { return vex3d(v); };
inline vex3ld operator""_vex3ld(unsigned long long v) { return vex3ld(v); };
inline vex3li operator""_vex3li(unsigned long long v) { return vex3li(v); };
inline vex3lli operator""_vex3lli(unsigned long long v) { return vex3lli(v); };

inline vex4f operator""_vex4f(unsigned long long v) { return vex4f(v); };
inline vex4i operator""_vex4i(unsigned long long v) { return vex4i(v); };
inline vex4ui operator""_vex4ui(unsigned long long v) { return vex4ui(v); };
inline vex4d operator""_vex4d(unsigned long long v) { return vex4d(v); };
inline vex4ld operator""_vex4ld(unsigned long long v) { return vex4ld(v); };
inline vex4li operator""_vex4li(unsigned long long v) { return vex4li(v); };
inline vex4lli operator""_vex4lli(unsigned long long v) { return vex4lli(v); };

inline vex2f operator""_vex2f(long double v) { return vex2f(v); };
inline vex2i operator""_vex2i(long double v) { return vex2i(v); };
inline vex2ui operator""_vex2ui(long double v) { return vex2ui(v); };
inline vex2d operator""_vex2d(long double v) { return vex2d(v); };
inline vex2ld operator""_vex2ld(long double v) { return vex2ld(v); };
inline vex2li operator""_vex2li(long double v) { return vex2li(v); };
inline vex2lli operator""_vex2lli(long double v) { return vex2lli(v); };

inline vex3f operator""_vex3f(long double v) { return vex3f(v); };
inline vex3i operator""_vex3i(long double v) { return vex3i(v); };
inline vex3ui operator""_vex3ui(long double v) { return vex3ui(v); };
inline vex3d operator""_vex3d(long double v) { return vex3d(v); };
inline vex3ld operator""_vex3ld(long double v) { return vex3ld(v); };
inline vex3li operator""_vex3li(long double v) { return vex3li(v); };
inline vex3lli operator""_vex3lli(long double v) { return vex3lli(v); };

inline vex4f operator""_vex4f(long double v) { return vex4f(v); };
inline vex4i operator""_vex4i(long double v) { return vex4i(v); };
inline vex4ui operator""_vex4ui(long double v) { return vex4ui(v); };
inline vex4d operator""_vex4d(long double v) { return vex4d(v); };
inline vex4ld operator""_vex4ld(long double v) { return vex4ld(v); };
inline vex4li operator""_vex4li(long double v) { return vex4li(v); };
inline vex4lli operator""_vex4lli(long double v) { return vex4lli(v); };

#ifdef __XSIMFUNCS__
__XSIMFUNCS__
#endif

#define _VexTypedefs_              \
typedef vex2<bool>          v2b;   \
typedef vex2<float>         v2f;   \
typedef vex2<int>           v2i;   \
typedef vex2<size_t>        v2ui;  \
typedef vex2<double>        v2d;   \
typedef vex2<long double>   v2ld;  \
typedef vex2<long int>      v2li;  \
typedef vex2<long long int> v2lli; \
typedef vex2<unsigned char> v2ub;   \
typedef vex2<std::string>   v2s;   \
                                   \
typedef vex3<bool>          v3b;   \
typedef vex3<float>         v3f;   \
typedef vex3<int>           v3i;   \
typedef vex3<size_t>        v3ui;  \
typedef vex3<double>        v3d;   \
typedef vex3<long double>   v3ld;  \
typedef vex3<long int>      v3li;  \
typedef vex3<long long int> v3lli; \
typedef vex3<unsigned char> v3ub;   \
typedef vex3<std::string>   v3s;   \
                                   \
typedef vex4<bool>          v4b;   \
typedef vex4<float>         v4f;   \
typedef vex4<int>           v4i;   \
typedef vex4<size_t>        v4ui;  \
typedef vex4<double>        v4d;   \
typedef vex4<long double>   v4ld;  \
typedef vex4<long int>      v4li;  \
typedef vex4<long long int> v4lli; \
typedef vex4<unsigned char> v4ub;   \
typedef vex4<std::string>   v4s;

#if !defined(_VEX_NO_SHORT_NAMES)
_VexTypedefs_
#endif

namespace std {
    inline vex2f ceil(vex2f v) { return vex2f(std::ceil(v.x), std::ceil(v.y)); };
    inline vex2d ceil(vex2d v) { return vex2d(std::ceil(v.x), std::ceil(v.y)); };
    inline vex2f floor(vex2f v) { return vex2f(std::floor(v.x), std::floor(v.y)); };
    inline vex2d floor(vex2d v) { return vex2d(std::floor(v.x), std::floor(v.y)); };
    inline vex2f round(vex2f v) { return vex2f(std::round(v.x), std::round(v.y)); };
    inline vex2d round(vex2d v) { return vex2d(std::round(v.x), std::round(v.y)); };
    inline vex2f trunc(vex2f v) { return vex2f(std::trunc(v.x), std::trunc(v.y)); };
    inline vex2d trunc(vex2d v) { return vex2d(std::trunc(v.x), std::trunc(v.y)); };
    inline vex2f exp(vex2f v) { return vex2f(std::exp(v.x), std::exp(v.y)); };
    inline vex2d exp(vex2d v) { return vex2d(std::exp(v.x), std::exp(v.y)); };
    template <typename T> inline vex2<T> abs(vex2<T> v) { return vex2<T>(std::abs(v.x), std::abs(v.y)); };
    template <typename T> inline vex2<T> sqrt(vex2<T> v) { return vex2<T>(std::sqrt(v.x), std::sqrt(v.y)); };
    template <typename T> inline vex2<T> cbrt(vex2<T> v) { return vex2<T>(std::cbrt(v.x), std::cbrt(v.y)); };
    template <typename T> inline vex2<T> pow(vex2<T> v, int p) { return vex2<T>(std::pow(v.x, p), std::pow(v.y, p)); };
    template <typename T> inline vex2<T>& max(vex2<T>& v1, vex2<T>& v2) { return (v1 > v2) ? v1 : v2; };
    template <typename T> inline vex2<T>& min(vex2<T>& v1, vex2<T>& v2) { return (v1 < v2) ? v1 : v2; };

    inline vex3f ceil(vex3f v) { return vex3f(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z)); };
    inline vex3d ceil(vex3d v) { return vex3f(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z)); };
    inline vex3f floor(vex3f v) { return vex3f(std::floor(v.x), std::floor(v.y), std::floor(v.z)); };
    inline vex3d floor(vex3d v) { return vex3d(std::floor(v.x), std::floor(v.y), std::floor(v.z)); };
    inline vex3f round(vex3f v) { return vex3f(std::round(v.x), std::round(v.y), std::round(v.z)); };
    inline vex3d round(vex3d v) { return vex3d(std::round(v.x), std::round(v.y), std::round(v.z)); };
    inline vex3f trunc(vex3f v) { return vex3f(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z)); };
    inline vex3d trunc(vex3d v) { return vex3d(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z)); };
    inline vex3f exp(vex3f v) { return vex3f(std::exp(v.x), std::exp(v.y), std::exp(v.z)); };
    inline vex3d exp(vex3d v) { return vex3d(std::exp(v.x), std::exp(v.y), std::exp(v.z)); };
    template <typename T> inline vex3<T> abs(vex3<T> v) { return vex3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z)); };
    template <typename T> inline vex3<T> sqrt(vex3<T> v) { return vex3<T>(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z)); };
    template <typename T> inline vex3<T> cbrt(vex3<T> v) { return vex3<T>(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z)); };
    template <typename T> inline vex3<T> pow(vex3<T> v, int p) { return vex3<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p)); };
    template <typename T> inline vex3<T>& max(vex3<T>& v1, vex3<T>& v2) { return (v1 > v2) ? v1 : v2; };
    template <typename T> inline vex3<T>& min(vex3<T>& v1, vex3<T>& v2) { return (v1 < v2) ? v1 : v2; };

    inline vex4f ceil(vex4f v) { return vex4f(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z), std::ceil(v.w)); };
    inline vex4d ceil(vex4d v) { return vex4f(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z), std::ceil(v.w)); };
    inline vex4f floor(vex4f v) { return vex4f(std::floor(v.x), std::floor(v.y), std::floor(v.z), std::floor(v.w)); };
    inline vex4d floor(vex4d v) { return vex4d(std::floor(v.x), std::floor(v.y), std::floor(v.z), std::floor(v.w)); };
    inline vex4f round(vex4f v) { return vex4f(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w)); };
    inline vex4d round(vex4d v) { return vex4d(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w)); };
    inline vex4f trunc(vex4f v) { return vex4f(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z), std::trunc(v.w)); };
    inline vex4d trunc(vex4d v) { return vex4d(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z), std::trunc(v.w)); };
    inline vex4d exp(vex4d v) { return vex4d(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w)); };
    inline vex4f exp(vex4f v) { return vex4f(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w)); };
    template <typename T> inline vex4<T> abs(vex4<T> v) { return vex4<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); };
    template <typename T> inline vex4<T> sqrt(vex4<T> v) { return vex4<T>(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z), std::sqrt(v.w)); };
    template <typename T> inline vex4<T> cbrt(vex4<T> v) { return vex4<T>(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z), std::cbrt(v.w)); };
    template <typename T> inline vex4<T> pow(vex4<T> v, int p) { return vex4<T>(std::pow(v.x, p), std::pow(v.y, p), std::pow(v.z, p), std::pow(v.w, p)); };
    template <typename T> inline vex4<T>& max(vex4<T>& v1, vex4<T>& v2) { return (v1 > v2) ? v1 : v2; };
    template <typename T> inline vex4<T>& min(vex4<T>& v1, vex4<T>& v2) { return (v1 < v2) ? v1 : v2; };
    template <typename T> vex2<T> stov2(const std::string& _s) {
        stringstream ss;
        string s;
        vex2<T> t;
        ss << _s;
        for (size_t i = 0u; i < 2u and ss >> s; i++)
            t[i] = sto<T>(s);
        return t;
    };
    template <typename T> vex3<T> stov3(const std::string& _s) {
        stringstream ss;
        string s;
        vex3<T> t;
        ss << _s;
        for (size_t i = 0u; i < 3u and ss >> s; i++)
            t[i] = sto<T>(s);
        return t;
    };
    template <typename T> vex4<T> stov4(const std::string& _s) {
        stringstream ss;
        string s;
        vex4<T> t;
        ss << _s;
        for (size_t i = 0u; i < 4u and ss >> s; i++)
            t[i] = sto<T>(s);
        return t;
    };
    template <typename T> std::string to_string(vex2<T> v, const std::string& sep = " ", const std::string& end = "") { return v.str(sep, end); };
    template <typename T> std::string to_string(vex3<T> v, const std::string& sep = " ", const std::string& end = "") { return v.str(sep, end); };
    template <typename T> std::string to_string(vex4<T> v, const std::string& sep = " ", const std::string& end = "") { return v.str(sep, end); };

    //template <unsigned n, typename T> T& get(vex2<T>&);
    //template <typename T> constexpr T& get<0>(vex2<T>& v) { return v.x; };
};

//template <> template <typename T> inline vex2<T> sto<vex2<T>>(const std::string& _str) { return std::stov2<T>(_str); };
//template <> template <typename T> inline vex3<T> sto<vex3<T>>(const std::string& _str) { return std::stov3<T>(_str); };
//template <> template <typename T> inline vex4<T> sto<vex4<T>>(const std::string& _str) { return std::stov4<T>(_str); };

template <typename T> std::vector<T>& operator+=(std::vector<T>& v, const vex2<T>& i) { v.emplace_back({ i.x, i.y }); return v; };
template <typename T> std::vector<T>& operator<<(std::vector<T>& v, const vex2<T>& i) { v.emplace_back({ i.x, i.y }); return v; };
template <typename T> std::vector<T> operator+(std::vector<T> v, const vex2<T>& i) { std::vector<T> t = v; t.emplace_back({ i.x, i.y }); return t; };
template <typename T> std::vector<T>& operator+=(std::vector<T>& v, const vex3<T>& i) { v.emplace_back({ i.x, i.y, i.z }); return v; };
template <typename T> std::vector<T>& operator<<(std::vector<T>& v, const vex3<T>& i) { v.emplace_back({ i.x, i.y, i.z }); return v; };
template <typename T> std::vector<T> operator+(std::vector<T> v, const vex3<T>& i) { std::vector<T> t = v; t.emplace_back({ i.x, i.y, i.z }); return t; };
template <typename T> std::vector<T>& operator+=(std::vector<T>& v, const vex4<T>& i) { v.emplace_back({ i.x, i.y, i.z, i.w }); return v; };
template <typename T> std::vector<T>& operator<<(std::vector<T>& v, const vex4<T>& i) { v.emplace_back({ i.x, i.y, i.z, i.w }); return v; };
template <typename T> std::vector<T> operator+(std::vector<T> v, const vex4<T>& i) { std::vector<T> t = v; t.emplace_back({ i.x, i.y, i.z, i.w }); return t; };

template <typename T> inline vex2<T> operator+(const char* l, const vex2<T>& r) { return std::stov2<T>(l) + r; };
template <typename T> inline vex2<T> operator-(const char* l, const vex2<T>& r) { return std::stov2<T>(l) - r; };
template <typename T> inline vex2<T> operator/(const char* l, const vex2<T>& r) { return std::stov2<T>(l) / r; };
template <typename T> inline vex2<T> operator*(const char* l, const vex2<T>& r) { return std::stov2<T>(l) * r; };

template <typename T> inline vex3<T> operator+(const char* l, const vex3<T>& r) { return std::stov3<T>(l) + r; };
template <typename T> inline vex3<T> operator-(const char* l, const vex3<T>& r) { return std::stov3<T>(l) - r; };
template <typename T> inline vex3<T> operator/(const char* l, const vex3<T>& r) { return std::stov3<T>(l) / r; };
template <typename T> inline vex3<T> operator*(const char* l, const vex3<T>& r) { return std::stov3<T>(l) * r; };

template <typename T> inline vex4<T> operator+(const char* l, const vex4<T>& r) { return std::stov4<T>(l) + r; };
template <typename T> inline vex4<T> operator-(const char* l, const vex4<T>& r) { return std::stov4<T>(l) - r; };
template <typename T> inline vex4<T> operator/(const char* l, const vex4<T>& r) { return std::stov4<T>(l) / r; };
template <typename T> inline vex4<T> operator*(const char* l, const vex4<T>& r) { return std::stov4<T>(l) * r; };

template <typename T> inline vex2<T> operator+(const int& l, const vex2<T>& r) { return vex2<T>(l) + r; };
template <typename T> inline vex2<T> operator-(const int& l, const vex2<T>& r) { return vex2<T>(l) - r; };
template <typename T> inline vex2<T> operator/(const int& l, const vex2<T>& r) { return vex2<T>(l) / r; };
template <typename T> inline vex2<T> operator*(const int& l, const vex2<T>& r) { return vex2<T>(l) * r; };
template <typename T> inline vex2<T> operator+(const float& l, const vex2<T>& r) { return vex2<T>(l) + r; };
template <typename T> inline vex2<T> operator-(const float& l, const vex2<T>& r) { return vex2<T>(l) - r; };
template <typename T> inline vex2<T> operator/(const float& l, const vex2<T>& r) { return vex2<T>(l) / r; };
template <typename T> inline vex2<T> operator*(const float& l, const vex2<T>& r) { return vex2<T>(l) * r; };
template <typename T> inline vex2<T> operator+(const double& l, const vex2<T>& r) { return vex2<T>(l) + r; };
template <typename T> inline vex2<T> operator-(const double& l, const vex2<T>& r) { return vex2<T>(l) - r; };
template <typename T> inline vex2<T> operator/(const double& l, const vex2<T>& r) { return vex2<T>(l) / r; };
template <typename T> inline vex2<T> operator*(const double& l, const vex2<T>& r) { return vex2<T>(l) * r; };

#if !defined(_VEX_NO_MATH_FUNCS)
template <typename T> vex2b limit(vex2<T>& v, const T& min, const T& max, const bool& _restart = false) {
    vex2b b = false;
    if (v.x < min) {
        v.x = _restart ? max : min;
        b.x = true;
    }
    else if (v.x > max) {
        v.x = _restart ? min : max;
        b.x = true;
    };
    if (v.y < min) {
        v.y = _restart ? max : min;
        b.y = true;
    }
    else if (v.y > max) {
        v.y = _restart ? min : max;
        b.y = true;
    };
    return b;
};
template <typename T> vex2b limit(vex2<T>& v, const vex2<T>& min, const vex2<T>& max, const bool& _restart = false) {
    vex2b b = false;
    if (v.x < min.x) {
        v.x = _restart ? max.x : min.x;
        b.x = true;
    }
    else if (v.x > max.x) {
        v.x = _restart ? min.x : max.x;
        b.x = true;
    };
    if (v.y < min.y) {
        v.y = _restart ? max.y : min.y;
        b.y = true;
    }
    else if (v.y > max.y) {
        v.y = _restart ? min.y : max.y;
        b.y = true;
    };
    return b;
};

template <typename T> vex3b limit(vex3<T>& v, const T& min, const T& max, const bool& _restart = false) {
    vex3b b = false;
    if (v.x < min) {
        v.x = _restart ? max : min;
        b.x = true;
    }
    else if (v.x > max) {
        v.x = _restart ? min : max;
        b.x = true;
    };
    if (v.y < min) {
        v.y = _restart ? max : min;
        b.y = true;
    }
    else if (v.y > max) {
        v.y = _restart ? min : max;
        b.y = true;
    };
    if (v.z < min) {
        v.z = _restart ? max : min;
        b.z = true;
    }
    else if (v.z > max) {
        v.z = _restart ? min : max;
        b.z = true;
    };
    return b;
};
template <typename T> vex3b limit(vex3<T>& v, const vex3<T>& min, const vex3<T>& max, const bool& _restart = false) {
    vex3b b = false;
    if (v.x < min.x) {
        v.x = _restart ? max.x : min.x;
        b.x = true;
    }
    else if (v.x > max.x) {
        v.x = _restart ? min.x : max.x;
        b.x = true;
    };
    if (v.y < min.y) {
        v.y = _restart ? max.y : min.y;
        b.y = true;
    }
    else if (v.y > max.y) {
        v.y = _restart ? min.y : max.y;
        b.y = true;
    };
    if (v.z < min.z) {
        v.z = _restart ? max.z : min.z;
        b.z = true;
    }
    else if (v.z > max.z) {
        v.z = _restart ? min.z : max.z;
        b.z = true;
    };
    return b;
};

template <typename T> vex4b limit(vex4<T>& v, const T& min, const T& max, const bool& _restart = false) {
    vex4b b = false;
    if (v.x < min) {
        v.x = _restart ? max : min;
        b.x = true;
    }
    else if (v.x > max) {
        v.x = _restart ? min : max;
        b.x = true;
    };
    if (v.y < min) {
        v.y = _restart ? max : min;
        b.y = true;
    }
    else if (v.y > max) {
        v.y = _restart ? min : max;
        b.y = true;
    };
    if (v.z < min) {
        v.z = _restart ? max : min;
        b.z = true;
    }
    else if (v.z > max) {
        v.z = _restart ? min : max;
        b.z = true;
    };
    if (v.w < min) {
        v.w = _restart ? max : min;
        b.w = true;
    }
    else if (v.w > max) {
        v.w = _restart ? min : max;
        b.w = true;
    };
    return v;
};
template <typename T> vex4b limit(vex4<T>& v, const vex4<T>& min, const vex4<T>& max, const bool& _restart = false) {
    vex4b b = false;
    if (v.x < min.x) {
        v.x = _restart ? max.x : min.x;
        b.x = true;
    }
    else if (v.x > max.x) {
        v.x = _restart ? min.x : max.x;
        b.x = true;
    };
    if (v.y < min.y) {
        v.y = _restart ? max.y : min.y;
        b.y = true;
    }
    else if (v.y > max.y) {
        v.y = _restart ? min.y : max.y;
        b.y = true;
    };
    if (v.z < min.z) {
        v.z = _restart ? max.z : min.z;
        b.z = true;
    }
    else if (v.z > max.z) {
        v.z = _restart ? min.z : max.z;
        b.z = true;
    };
    if (v.w < min.w) {
        v.w = _restart ? max.w : min.w;
        b.w = true;
    }
    else if (v.w > max.w) {
        v.w = _restart ? min.w : max.w;
        b.w = true;
    };
    return v;
};

inline vex2f lerp(const vex2f& a, const vex2f& b, const vex2f& t) { return {std::lerp(a.x,b.x,t.x),std::lerp(a.y,b.y,t.y)}; };
inline vex3f lerp(const vex3f& a, const vex3f& b, const vex3f& t) { return {std::lerp(a.x,b.x,t.x),std::lerp(a.y,b.y,t.y),std::lerp(a.z,b.z,t.z)}; };
inline vex4f lerp(const vex4f& a, const vex4f& b, const vex4f& t) { return {std::lerp(a.x,b.x,t.x),std::lerp(a.y,b.y,t.y),std::lerp(a.z,b.z,t.z),std::lerp(a.w,b.w,t.w)}; };
template <typename T> inline vex2<T> mix(const vex2<T>& a, const vex2<T>& b) { return (a + b) / 2; };
template <typename T> inline vex3<T> mix(const vex3<T>& a, const vex3<T>& b) { return (a + b) / 2; };
template <typename T> inline vex4<T> mix(const vex4<T>& a, const vex4<T>& b) { return (a + b) / 2; };

template <typename T> inline const T& max(const vex2<T>& v) { return (v.x > v.y) ? v.x : v.y; };
template <typename T> inline const T& max(const vex3<T>& v) { return (v.x > v.y && v.x > v.z) ? v.x : (v.y > v.z) ? v.y : v.z; };
template <typename T> inline const T& max(const vex4<T>& v) { return (v.x > v.y && v.x > v.z && v.x > v.w) ? v.x : (v.y > v.z && v.y > v.w) ? v.y : (v.z > v.w) ? v.z : v.w; };

template <typename T> inline const T& min(const vex2<T>& v) { return (v.x < v.y) ? v.x : v.y; };
template <typename T> inline const T& min(const vex3<T>& v) { return (v.x < v.y&& v.x < v.z) ? v.x : (v.y < v.z) ? v.y : v.z; };
template <typename T> inline const T& min(const vex4<T>& v) { return (v.x < v.y&& v.x < v.z&& v.x < v.w) ? v.x : (v.y < v.z && v.y < v.w) ? v.y : (v.z < v.w) ? v.z : v.w; };
#endif
#endif