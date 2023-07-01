#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct Point {
    ld x = 0, y = 0, z = 0;
    Point operator^(const Point &other) const {
        return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
    }
    ld operator*(const Point &other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    bool operator==(const Point &other) const {
        return abs(x - other.x) < 1e-3 && abs(y - other.y) < 1e-3 && abs(z - other.z) < 1e-3;
    }
    bool operator!=(const Point &other) const {
        return !(*this == other);
    }
};

ld dist(const Point &a, const Point &b) {
    return sqrt((b - a) * (b - a));
}

ld mag(const Point &a) {
    return sqrt(a * a);
}

ld area(const Point &a, const Point &b, const Point &c) {
    return mag((b - a) ^ (c - a)) / 2;
}

bool collinear(const Point &a, const Point &b, const Point &c) {
    return ((b - a) ^ (c - a)) == Point();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        Point a, b, c, d;
        cin >> a.x >> a.y >> a.z;
        if (a.x == 0 && a.y == 0 && a.z == 0) {
            break;
        }
        cin >> b.x >> b.y >> b.z >> c.x >> c.y >> c.z >> d.x >> d.y >> d.z;
        if (collinear(a, b, c)) {
            if (abs(dist(a, b) - dist(a, d) - dist(b, d)) < 1e-3 && a != d && b != d) {
                cout << "YES\n";
            } elif (abs(dist(a, c) - dist(a, d) - dist(c, d)) < 1e-3 && a != d && c != d) {
                cout << "YES\n";
            } elif (abs(dist(b, c) - dist(b, d) - dist(c, d)) < 1e-3 && b != d && c != d) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } elif (abs(area(a, b, c) - area(a, b, d) - area(a, c, d) - area(b, c, d)) < 1e-3 &&
                abs(dist(a, b) - dist(a, d) - dist(b, d)) > 1e-3 &&
                abs(dist(a, c) - dist(a, d) - dist(c, d)) > 1e-3 &&
                abs(dist(b, c) - dist(b, d) - dist(c, d)) > 1e-3) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}