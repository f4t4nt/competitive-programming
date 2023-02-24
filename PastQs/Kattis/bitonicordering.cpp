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

struct SegTree {
    ll n;
    vector<ll> data;
    SegTree (ll n) :
        n(n),
        data(4 * n, 0) {}
    void update(ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (lo <= l && r <= hi) {
            data[i]++;
            return;
        }
        if (r <= lo || hi <= l) {
            return;
        }
        ll m = (l + r) / 2;
        update(lo, hi, 2 * i, l, m);
        update(lo, hi, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll query(ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
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

    ll n;
    cin >> n;
    vector<pair<ll, ll>> c(n);
    FOR (i, n) {
        cin >> c[i].first;
        c[i].second = i;
    }
    rsort(c);
    SegTree st(n);
    ll rv = 0;
    FORE (x, c) {
        rv += min(st.query(0, x.second), st.query(x.second, n));
        st.update(x.second, x.second + 1);
    }
    cout << rv << '\n';

    return 0;
}