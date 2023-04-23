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

    Point() : x(0), y(0) {}

    Point(ld x, ld y) : x(x), y(y) {}

    Point operator+(const Point &p) const {
        return Point(x + p.x, y + p.y);
    }

    Point operator-(const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    Point operator*(const ld &k) const {
        return Point(x * k, y * k);
    }

    Point operator/(const ld &k) const {
        return Point(x / k, y / k);
    }

    ld operator*(const Point &p) const {
        return x * p.x + y * p.y;
    }

    ld operator^(const Point &p) const {
        return x * p.y - y * p.x;
    }

    bool operator==(const Point &p) const {
        return abs(x - p.x) < EPS && abs(y - p.y) < EPS;
    }

    ld len() const {
        return sqrt(x * x + y * y);
    }

    ld len2() const {
        return x * x + y * y;
    }
};

bool lex(const Point &a, const Point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

Point o;

bool comp(const Point &a, const Point &b) {
    bool lex_a = lex(o, a), lex_b = lex(o, b);
    if (lex_a != lex_b) {
        return lex_a < lex_b;
    }
    return ((a - o) ^ (b - o)) > 0;
}

ld dist(const Point &a, const Point &b) {
    return (a - b).len();
}

ld dist2(const Point &a, const Point &b) {
    return (a - b).len2();
}

struct Circle {
    Point c;
    ld r;
    
    bool contains(const Point &p) const {
        return dist2(c, p) <= r * r;
    }
};

vector<Point> intersect(const Circle &a, const Circle &b) {
    ld d = dist(a.c, b.c);
    if (d > a.r + b.r || d < abs(a.r - b.r)) {
        return {};
    }
    ld x = (d * d + a.r * a.r - b.r * b.r) / (2 * d);
    ld y = sqrt(a.r * a.r - x * x);
    Point v = (b.c - a.c) / d;
    return {a.c + v * x + Point(-v.y, v.x) * y, a.c + v * x - Point(-v.y, v.x) * y};
}

struct Intersection {
    ll to;
    Point p;
    bool left, vis = false;
};

ld area(const vector<Point> &p) {
    ld rv = 0;
    FOR (i, sz(p)) {
        rv += (p[(i + 1) % sz(p)] ^ p[i]);
    }
    return rv / 2;
}

void add_intersection(
    vector<vector<Intersection>> &g,
    const vector<Circle> &circles,
    ll i,
    ll j,
    const Point &p
) {
    FOR (k, sz(circles)) {
        if (k != i && k != j && circles[k].contains(p)) {
            return;
        }
    }
    Intersection inter;
    inter.left = true;
    inter.to = j;
    inter.p = p;
    g[i].pb(inter);
    inter.left = false;
    inter.to = i;
    g[j].pb(inter);
}

void dfs(
    vector<vector<Intersection>> &g,
    vector<Point> &path,
    ll i,
    Intersection &inter
) {
    if (inter.vis) {
        return;
    }
    inter.vis = true;
    path.pb(inter.p);
    auto &v = g[inter.to];
    FOB (it, v.begin(), v.end()) {
        if (it->p == inter.p) {
            it->vis = true;
            if (next(it) == v.end()) {
                it = v.begin();
            } else {
                it++;
            }
            dfs(g, path, inter.to, *it);
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<Circle> circles(n);
        FOR (i, n) {
            cin >> circles[i].c.x >> circles[i].c.y >> circles[i].r;
        }
        vector<vector<Intersection>> g(n);
        FOR (i, n) {
            FOB (j, i + 1, n) {
                auto ps = intersect(circles[i], circles[j]);
                if (sz(ps) == 2) {
                    add_intersection(g, circles, i, j, ps[0]);
                    add_intersection(g, circles, j, i, ps[1]);
                }
            }
        }
        FOR (i, n) {
            auto &v = g[i];
            o = circles[i].c;
            sort(all(v), [](const Intersection &a, const Intersection &b) {
                return comp(a.p, b.p);
            });
        }
        // FOR (i, n) {
        //     cout << i << ": ";
        //     for (auto &inter : g[i]) {
        //         cout << inter.to << ' ' << inter.p.x << ' ' << inter.p.y << ' ' << inter.left << ' ' << inter.vis << " | ";
        //     }
        //     cout << '\n';
        // }
        ll rv = 1;
        FOR (i, n) {
            FORE (inter, g[i]) {
                if (!inter.vis && !inter.left) {
                    vector<Point> path;
                    dfs(g, path, i, inter);
                    // FOR (k, sz(path)) {
                    //     cout << path[k].x << ' ' << path[k].y << " | ";
                    // }
                    // cout << '\n';
                    // cout << "area: " << area(path) << '\n';
                    if (area(path) > 0) {
                        rv++;
                    }
                }
            }
        }
        cout << rv << '\n';
    }

    return 0;
}