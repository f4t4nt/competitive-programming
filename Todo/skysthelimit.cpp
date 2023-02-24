#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld n, k;
    cin >> n >> k;
    n += 2;
    vector<ld> h(n), d(n), g(n), f(n), rv(n);
    FOR (i, n - 2) {
        cin >> h[i + 1];
    }
    FOR (i, n) {
        d[i] = k * i * i;
        g[i] = h[i] + d[i];
    }
    vector<pair<ld, ld>> hull;
    FOR (i, n) {
        while (hull.size() >= 2) {
            ll a, b, c, d;
            tie(a, b) = hull[hull.size() - 2];
            tie(c, d) = hull[hull.size() - 1];
            if (a * (i - d) - c * (i - d) >= b * (g[i] - c) - d * (g[i] - c)) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.pb({g[i], i});
    }
    bool updated = true;
    ld i = 0, curr_idx = 0, m, b;
    while (i < n - 1) {
        while (curr_idx < hull.size() - 1 && hull[curr_idx + 1].second < i) {
            curr_idx++;
            updated = true;
        }
        if (updated) {
            m = (hull[curr_idx + 1].first - hull[curr_idx].first) / (hull[curr_idx + 1].second - hull[curr_idx].second);
            b = hull[curr_idx].first - m * hull[curr_idx].second;
            updated = false;
        }
        f[i] = m * i + b;
        i++;
    }
    f[n - 1] = g[n - 1];
    FOR (i, n) {
        while(f[i] < g[i]) {
            f[i] = -1;
        }
        assert(f[i] >= g[i]);
    }
    FOR (i, n) {
        rv[i] = f[i] - d[i];
    }
    ld max_rv = 0;
    FOR (i, n) {
        max_rv = max(max(max_rv, rv[i]), h[i]);
    }
    cout << setprecision(10) << max_rv << '\n';
    
    return 0;
}