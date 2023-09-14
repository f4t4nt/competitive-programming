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
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

void insert(ll &x, ll &lo_sz, ll &hi_sz, map<ll, ll> &lo, map<ll, ll> &hi) {
    if (lo_sz == 0 || x <= lo.rbegin()->first) {
        lo[x]++;
        lo_sz++;
    } else {
        hi[x]++;
        hi_sz++;
    }
}

void remove(ll &x, ll &lo_sz, ll &hi_sz, map<ll, ll> &lo, map<ll, ll> &hi) {
    if (lo.count(x)) {
        lo_sz--;
        lo[x]--;
        if (lo[x] == 0) {
            lo.erase(x);
        }
    } else {
        hi_sz--;
        hi[x]--;
        if (hi[x] == 0) {
            hi.erase(x);
        }
    }
}

void adjust(ll &lo_sz, ll &hi_sz, map<ll, ll> &lo, map<ll, ll> &hi) {
    if (lo_sz > hi_sz + 1) {
        ll y = lo.rbegin()->first;
        lo_sz--;
        lo[y]--;
        if (lo[y] == 0) {
            lo.erase(y);
        }
        hi[y]++;
        hi_sz++;
    } else if (hi_sz > lo_sz) {
        ll y = hi.begin()->first;
        hi_sz--;
        hi[y]--;
        if (hi[y] == 0) {
            hi.erase(y);
        }
        lo[y]++;
        lo_sz++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    FORE (x, a) {
        cin >> x;
    }
    ll lo_sz = 0, hi_sz = 0;
    map<ll, ll> lo, hi;
    FOR (i, n) {
        insert(a[i], lo_sz, hi_sz, lo, hi);
        adjust(lo_sz, hi_sz, lo, hi);
        if (lo_sz + hi_sz == k) {
            cout << lo.rbegin()->first << ' ';
            remove(a[i - k + 1], lo_sz, hi_sz, lo, hi);
            adjust(lo_sz, hi_sz, lo, hi);
        }
    }
 
    return 0;
}