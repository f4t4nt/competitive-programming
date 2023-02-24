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

// https://open.kattis.com/problems/evensubstrings

struct SegTree {
    ll n;
    // xor of whole range
    // prefix xor counts
    vector<pair<ll, vector<ll>>> data;
    vector<vector<pair<ll, ll>>> lazy;
    SegTree (ll n) :
        n(n),
        data(4 * n, {0, vector<ll>(1 << 6)}),
        lazy(4 * n) {}
    // [lo, hi)
    void update(ll idx, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (!lazy[i].empty()) { 
            data[i] += (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (idx <= l && r <= idx + 1) {
            data[i] += (r - l) * val;
            if (r - l > 1) {
                lazy[2 * i] += val;
                lazy[2 * i + 1] += val;
            }
            return;
        }
        if (r <= idx || idx < l) {
            return;
        }
        ll m = (l + r) / 2;
        update(idx, val, 2 * i, l, m);
        update(idx, val, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    pair<ll, vector<ll>> query(ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (lazy[i] != 0) {
            data[i] += (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (lo <= l && r <= hi) {
            return data[i];
        }
        if (r <= lo || hi <= l) {
            return 0;
        }
        ll m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    str s;
    cin >> s;
    ll q;
    cin >> q;

    FOR ()

    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r;
            cin >> l >> r;
            vector<ll> rv;
            tie(ignore, rv) = 
        } elif (t == 2) {
            ll i;
            ch x;

        }
    }

    return 0;
}