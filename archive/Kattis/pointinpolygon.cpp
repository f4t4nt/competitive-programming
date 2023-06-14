#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

constexpr ld EPS = 1e-6;

struct Point {
    ld x, y;
};

ll det(Point a, Point b, Point c, Point d) {
    return (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
}

ll dir(Point a, Point b, Point c) {
    ll rv = det(a, b, a, c);
    if (rv > 0) {
        return 1;
    } elif (rv < 0) {
        return -1;
    } else {
        return 0;
    }
}
bool point_on_segment(Point p, Point a, Point b) {
    if (dir(p, a, b) != 0) {
        return false;
    }
    bool rv = min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
    return rv;
}

bool segments_intersect(Point a, Point b, Point c, Point d) {
    bool rv1 = dir(a, b, c) != dir(a, b, d),
            rv2 = dir(c, d, a) != dir(c, d, b);
    return rv1 && rv2;
}

ll point_in_polygon(Point p, vector<Point> &v) {
    ll n = sz(v);
    ll rv = 0;
    Point inf = {1e5, p.y + 1};
    FOR (i, n) {
        Point a = v[i];
        Point b = v[(i + 1) % n];
        if (a.y > b.y) {
            swap(a, b);
        }
        if (point_on_segment(p, a, b)) {
            return 2;
        }
        if (segments_intersect(p, inf, a, b)) {
            rv ^= 1;
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n, q;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<Point> v(n);
        FOR (i, n) {
            cin >> v[i].x >> v[i].y;
        }
        cin >> q;
        Point p;
        while (q--) {
            cin >> p.x >> p.y;
            ll rv = point_in_polygon(p, v);
            if (rv == 0) {
                cout << "out\n";
            } elif (rv == 1) {
                cout << "in\n";
            } else {
                cout << "on\n";
            }
        }
    }

    return 0;
}