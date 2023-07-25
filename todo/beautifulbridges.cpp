#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

// https://open.kattis.com/problems/beautifulbridges

bool valid(ll l, ll r, ll h, vector<pair<ll, ll>> &g) {
    ld rad = (ld) (g[r].first - g[l].first) / 2;
    pair<ld, ld> c = {(ld) (g[r].first + g[l].first) / 2, h - rad};
    FOB (i, l, r + 1) {
        if (g[i].second <= c.second) {
            continue;
        }
        ld dist = sqrt(pow(g[i].first - c.first, 2) + pow(g[i].second - c.second, 2));
        if (dist > rad) {
            return false;
        }
    }
    return true;
}

pair<ll, ll> get_bounds(ll i, ll n, ll h, vector<pair<ll, ll>> &g) {
    pair<ll, ll> rv;
    ll lo = 0, hi = i;
    // left bound
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (valid(mid, i, h, g)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    rv.first = lo;
    lo = i, hi = n - 1;
    // right bound
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;
        if (valid(i, mid, h, g)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    rv.second = hi;
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, h, a, b;
    cin >> n >> h >> a >> b;
    vector<pair<ll, ll>> g(n), bounds(n);
    FOR (i, n) {
        cin >> g[i].first >> g[i].second;
    }
    g.pb(g.back());
    n++;
    FOR (i, n) {
        bounds[i] = get_bounds(i, n, h, g);
    }
    vector<ll> dp(n);

    return 0;
}