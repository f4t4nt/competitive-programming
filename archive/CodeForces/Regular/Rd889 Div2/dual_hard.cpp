#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

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

vector<pair<ll, ll>> solve_pos(vector<ll> &a) {
    if (sz(a) == 0) {
        return {};
    }
    ll max_a = -1e18, max_i = -1,
        min_a = 1e18, min_i = -1;
    FOR (i, sz(a)) {
        if (a[i] > max_a) {
            max_a = a[i];
            max_i = i;
        }
        if (a[i] < min_a) {
            min_a = a[i];
            min_i = i;
        }
    }
    if (max_a <= 0) {
        return vector<pair<ll, ll>>(32);
    }
    vector<pair<ll, ll>> rv;
    while (a[max_i] < -min_a) {
        rv.pb({max_i, max_i});
        a[max_i] += a[max_i];
    }
    FOR (i, sz(a)) {
        if (a[i] < 0) {
            rv.pb({i, max_i});
            a[i] += a[max_i];
        }
    }
    FOR (i, sz(a) - 1) {
        if (a[i] > a[i + 1]) {
            rv.pb({i + 1, i});
            a[i + 1] += a[i];
        }
    }
    assert(is_sorted(all(a)));
    return rv;
}

vector<pair<ll, ll>> solve_neg(vector<ll> &a) {
    if (sz(a) == 0) {
        return {};
    }
    ll max_a = -1e18, max_i = -1,
        min_a = 1e18, min_i = -1;
    FOR (i, sz(a)) {
        if (a[i] > max_a) {
            max_a = a[i];
            max_i = i;
        }
        if (a[i] < min_a) {
            min_a = a[i];
            min_i = i;
        }
    }
    if (min_a >= 0) {
        return vector<pair<ll, ll>>(32);
    }
    vector<pair<ll, ll>> rv;
    while (a[min_i] > -max_a) {
        rv.pb({min_i, min_i});
        a[min_i] += a[min_i];
    }
    FOR (i, sz(a)) {
        if (a[i] > 0) {
            rv.pb({i, min_i});
            a[i] += a[min_i];
        }
    }
    FORR (i, sz(a) - 1) {
        if (a[i] > a[i + 1]) {
            rv.pb({i, i + 1});
            a[i] += a[i + 1];
        }
    }
    assert(is_sorted(all(a)));
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, cnt_pos = 0, cnt_neg = 0;
        pair<ll, ll> max_a = {-1e18, -1}, min_a = {1e18, -1};
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
            cnt_pos += (a[i] > 0);
            cnt_neg += (a[i] < 0);
            if (a[i] > max_a.first) {
                max_a = {a[i], i};
            }
            if (a[i] < min_a.first) {
                min_a = {a[i], i};
            }
        }
        if (is_sorted(all(a))) {
            cout << 0 << '\n';
            continue;
        }
        vector<pair<ll, ll>> rv(32);
        FOR (idx, n + 1) {
            vector<ll> a_lo = a, a_hi = a;
            a_lo.resize(idx);
            a_hi.erase(a_hi.begin(), a_hi.begin() + idx);
            vector<pair<ll, ll>> rv_lo, rv_hi;
            rv_lo = solve_neg(a_lo);
            rv_hi = solve_pos(a_hi);
            FORE (e, rv_hi) {
                e.first += idx;
                e.second += idx;
            }
            FORE (e, rv_hi) {
                rv_lo.pb(e);
            }
            if (sz(rv_lo) < sz(rv)) {
                rv = rv_lo;
            }
        }
        assert(sz(rv) <= 31);
        cout << sz(rv) << '\n';
        FORE (x, rv) {
            cout << x.first + 1 << ' ' << x.second + 1 << '\n';
        }
    }

    return 0;
}