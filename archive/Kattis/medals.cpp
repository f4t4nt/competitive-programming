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
    Point operator/(const ld &other) const {
        return {x / other, y / other, z / other};
    }
    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
};

ld tetra_vol(vector<Point> tetra) {
    assert(sz(tetra) == 4);
    return abs((tetra[1] - tetra[0]) * ((tetra[2] - tetra[0]) ^ (tetra[3] - tetra[0]))) / 6;
}

bool pt_in_tetra(Point pt, vector<Point> tetra) {
    assert(sz(tetra) == 4);
    ld vol0 = tetra_vol(tetra),
        vol1 = tetra_vol({tetra[0], tetra[1], tetra[2], pt}) +
            tetra_vol({tetra[0], tetra[1], tetra[3], pt}) +
            tetra_vol({tetra[0], tetra[2], tetra[3], pt}) +
            tetra_vol({tetra[1], tetra[2], tetra[3], pt});
    return abs(vol0 - vol1) < 1e-9 && vol0 > 1e-9;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ld n;
        cin >> n;
        if (n == 0) break;
        vector<pair<str, Point>> res(n);
        Point canada = {-1, -1, -1}, maxx = {0, 0, 0}, maxy = {0, 0, 0}, maxz = {0, 0, 0};
        FOR(i, n) {
            str name;
            ld x, y, z;
            cin >> name >> x >> y >> z;
            res[i] = {name, {x, y, z}};
            if (name == "Canada") canada = res[i].second;
            else {
                res.pb({name + "x", {0, y, z}});
                res.pb({name + "y", {x, 0, z}});
                res.pb({name + "z", {x, y, 0}});
                res.pb({name + "X", {x, 0, 0}});
                res.pb({name + "Y", {0, y, 0}});
                res.pb({name + "Z", {0, 0, z}});
            }
        }
        if (canada.x == -1) {
            cout << "Canada cannot win.\n";
            continue;
        }
        res.pb({"0", {0, 0, 0}});
        bool ok = true;
        n = sz(res);
        FOR (i, n) {
            if (res[i].first == "Canada") continue;
            FOB (j, i + 1, n) {
                if (res[j].first == "Canada") continue;
                FOB (k, j + 1, n) {
                    if (res[k].first == "Canada") continue;
                    FOB (l, k + 1, n) {
                        if (res[l].first == "Canada") continue;
                        if (pt_in_tetra(canada, {res[i].second, res[j].second, res[k].second, res[l].second})) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) break;
                }
                if (!ok) break;
            }
        }
        if (ok) cout << "Canada wins!\n";
        else cout << "Canada cannot win.\n";
    }

    return 0;
}