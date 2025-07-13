#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;
typedef long double ld;

inline i128 iabs(i128 x) { return x < 0 ? -x : x; }

struct frac {
    i128 num, den;

    frac(i128 n = 0, i128 d = 1) {
        assert(d != 0);
        i128 g = __gcd(iabs(n), iabs(d));
        n /= g; d /= g;
        if (d < 0) n = -n, d = -d;
        num = n, den = d;
    }

    void normalize() {
        assert(den != 0);
        i128 g = __gcd(iabs(num), iabs(den));
        num /= g; den /= g;
        if (den < 0) num = -num, den = -den;
    }

    frac& operator+=(i128 o) { return *this += frac(o); }
    frac& operator-=(i128 o) { return *this -= frac(o); }
    frac& operator*=(i128 o) { return *this *= frac(o); }
    frac& operator/=(i128 o) { return *this /= frac(o); }

    friend frac operator+(frac a, i128 b) { return a += b; }
    friend frac operator-(frac a, i128 b) { return a -= b; }
    friend frac operator*(frac a, i128 b) { return a *= b; }
    friend frac operator/(frac a, i128 b) { return a /= b; }

    friend frac operator+(i128 a, frac b) { return b += a; }
    friend frac operator-(i128 a, frac b) { return frac(a) -= b; }
    friend frac operator*(i128 a, frac b) { return b *= a; }
    friend frac operator/(i128 a, frac b) { return frac(a) /= b; }

    frac& operator+=(const frac &o) {
        num = num * o.den + o.num * den;
        den = den * o.den;
        normalize(); return *this;
    }
    frac& operator-=(const frac &o) {
        num = num * o.den - o.num * den;
        den = den * o.den;
        normalize(); return *this;
    }
    frac& operator*=(const frac &o) {
        num *= o.num;
        den *= o.den;
        normalize(); return *this;
    }
    frac& operator/=(const frac &o) {
        if (o.num == 0) throw invalid_argument("division by zero");
        num *= o.den;
        den *= o.num;
        normalize(); return *this;
    }

    friend frac operator+(frac a, const frac &b) { return a += b; }
    friend frac operator-(frac a, const frac &b) { return a -= b; }
    friend frac operator*(frac a, const frac &b) { return a *= b; }
    friend frac operator/(frac a, const frac &b) { return a /= b; }

    frac operator-() const { return frac(-num, den); }

    friend bool operator==(const frac &a, const frac &b) { return a.num == b.num && a.den == b.den; }
    friend bool operator!=(const frac &a, const frac &b) { return !(a == b); }
    friend bool operator<(const frac &a, const frac &b)  { return a.num * b.den < b.num * a.den; }
    friend bool operator<=(const frac &a, const frac &b) { return a < b || a == b; }
    friend bool operator>(const frac &a, const frac &b)  { return b < a; }
    friend bool operator>=(const frac &a, const frac &b) { return !(a < b); }

    explicit operator ld() const { return (ld)num / (ld)den; }

    friend ostream& operator<<(ostream &os, const frac &f) {
        return os << (long long)f.num << '/' << (long long)f.den;
    }
    friend istream& operator>>(istream &is, frac &f) {
        long long n, d = 1; char ch;
        is >> n;
        if (is.peek() == '/') is >> ch >> d;
        f = frac(n, d);
        return is;
    }
};
