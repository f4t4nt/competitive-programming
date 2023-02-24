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

struct SegTree {
    ll n;
    vector<ll> data, lazy;
    SegTree (ll n) :
        n(n),
        data(4 * n, 0),
        lazy(4 * n, 0) {}
    void update(ll idx, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (l == r - 1) {
            data[i] = val;
            return;
        }
        ll m = (l + r) / 2;
        if (idx < m) {
            update(idx, val, 2 * i, l, m);
        } else {
            update(idx, val, 2 * i + 1, m, r);
        }
        data[i] = min(data[2 * i], data[2 * i + 1]);
    }
    ll query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (ql <= l && r <= qr) {
            return data[i];
        }
        if (r <= ql || qr <= l) {
            return LLONG_MAX;
        }
        ll m = (l + r) / 2;
        return min(query(ql, qr, 2 * i, l, m), query(ql, qr, 2 * i + 1, m, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<ll> x(n);
    FOR (i, n) {
        cin >> x[i];
    }

    SegTree st(n);
    FOR (i, n) {
        st.update(i, x[i]);
    }

    while (q--) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        cout << st.query(a, b + 1) << '\n';
    }

    return 0;
}