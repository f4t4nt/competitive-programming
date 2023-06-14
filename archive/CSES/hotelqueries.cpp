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
    vector<ll> data;
    SegTree(ll n, vector<ll> &a) :
        n(n),
        data(4 * n, 0) {
        build(1, 0, n - 1, a);
    }
    void build(ll i, ll l, ll r, vector<ll> &a) {
        if (l == r) {
            data[i] = a[l];
        } else {
            ll m = (l + r) / 2;
            build(2 * i, l, m, a);
            build(2 * i + 1, m + 1, r, a);
            data[i] = max(data[2 * i], data[2 * i + 1]);
        }
    }
    pair<ll, ll> query(ll val, ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n - 1;
        }
        if (lo > r || hi < l) {
            return mp(-1, -1);
        }
        if (lo <= l && r <= hi) {
            if (data[i] < val) {
                return mp(-1, -1);
            }
            if (l == r) {
                data[i] -= val;
                return mp(l, data[i]);
            }
        }
        ll m = (l + r) / 2;
        pair<ll, ll> rv = query(val, lo, hi, 2 * i, l, m);
        if (rv.first == -1) {
            rv = query(val, lo, hi, 2 * i + 1, m + 1, r);
        }
        data[i] = max(data[2 * i], data[2 * i + 1]);
        return rv;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> h(n);
    FOR (i, n) {
        cin >> h[i];
    }
    SegTree st(n, h);

    FOR (i, m) {
        ll r;
        cin >> r;
        pair<ll, ll> rv = st.query(r, 0, n - 1);
        cout << rv.first + 1 << ' ';
    }

    return 0;
}