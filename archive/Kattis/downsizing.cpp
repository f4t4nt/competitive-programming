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

ld cross(ld x0, ld y0, ld x1, ld y1) {
    return x0 * y1 - x1 * y0;
}

pair<ld, ld> project(ld x, ld y, ld r) {
    ld ratio = r * r / (x * x + y * y);
    return {x * ratio, y * ratio};
}

ld solve(ll res, vector<pair<ld, ld>> &v, ld r) {
    ld area = 0, x0, y0, x1, y1;
    tie(x0, y0) = project(v[0].first, v[0].second, r);
    FOR (j, sz(v)) {
        ll j2 = (j + 1) % sz(v);
        FOR (i, res) {
            x1 = x0, y1 = y0;
            ld x = v[j].first + (v[j2].first - v[j].first) * (i + 1) / res;
            ld y = v[j].second + (v[j2].second - v[j].second) * (i + 1) / res;
            tie(x0, y0) = project(x, y, r);
            area += cross(x1, y1, x0, y0);
        }
    }
    area = abs(area);
    area /= 2;
    return area;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ld x0, y0, r;
    cin >> x0 >> y0 >> r;
    ll n;
    cin >> n;
    vector<pair<ld, ld>> v(n);
    FOR (i, n) {
        cin >> v[i].first >> v[i].second;
        v[i].first -= x0;
        v[i].second -= y0;
    }
    
    ll res = 10000;
    ld cur = 1, prev = 0;
    while ((cur - prev) / cur > 1e-6) {
        prev = cur;
        cur = solve(res, v, r);
        res *= 2;
    }

    cout << fixed << setprecision(10) << cur << '\n';
    
    return 0;
}