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
    vector<pair<ll, ll>> data;
    SegTree(ll n, vector<ll> &a) :
        n(n),
        data(4 * n, {0, 0}) {
        build(1, 0, n - 1, a);
    }
    void build(ll i, ll l, ll r, vector<ll> &a) {
        if (l == r) {
            data[i].first = 1;
            data[i].second = a[l];
        } else {
            ll m = (l + r) / 2;
            build(2 * i, l, m, a);
            build(2 * i + 1, m + 1, r, a);
            data[i].first = data[2 * i].first + data[2 * i + 1].first;
            data[i].second = data[2 * i].second + data[2 * i + 1].second;
        }
    }
    ll query(ll idx, ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n - 1;
        }
        if (lo > r || hi < l) {
            return 0;
        }
        if (idx <= data[i].first) {
            if (l == r) {
                data[i].first = 0;
                return data[i].second;
            } else {
                ll m = (l + r) / 2;
                ll res = query(idx, lo, hi, 2 * i, l, m);
                if (res == -1) {
                    res = query(idx - data[2 * i].first, lo, hi, 2 * i + 1, m + 1, r);
                }
                data[i].first = data[2 * i].first + data[2 * i + 1].first;
                data[i].second = data[2 * i].second + data[2 * i + 1].second;
                return res;
            }
        } else {
            return -1;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> h(n);
    FOR (i, n) {
        cin >> h[i];
    }
    SegTree st(n, h);

    FOR (i, n) {
        ll r;
        cin >> r;
        cout << st.query(r, 0, n - 1) << ' ';
    }
    return 0;
}