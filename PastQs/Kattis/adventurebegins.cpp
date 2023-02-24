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

constexpr ll MOD = 1e9 + 7;

vector<ll> inv_map = vector<ll>(1e5 + 10, -1);

struct mod_ll {
    ll val;
    mod_ll(ll v = 0) : val(((v % MOD) + MOD) % MOD) {}
    mod_ll operator+(const mod_ll &other) const { return mod_ll(val + other.val); }
    mod_ll operator-(const mod_ll &other) const { return mod_ll(val - other.val); }
    mod_ll operator*(const mod_ll &other) const { return mod_ll(val * other.val); }
    mod_ll pow(ll p) const {
        mod_ll rv = 1;
        mod_ll base = *this;
        while (p) {
            if (p & 1) rv = rv * base;
            base = base * base;
            p >>= 1;
        }
        return rv;
    }
    mod_ll inv() const {
        if (inv_map[val] != -1) return mod_ll(inv_map[val]);
        return inv_map[val] = pow(MOD - 2).val;
    }
    mod_ll operator/(const mod_ll &other) const { return *this * other.inv(); }
    mod_ll &operator+=(const mod_ll &other) { return *this = *this + other; }
    mod_ll &operator-=(const mod_ll &other) { return *this = *this - other; }
    mod_ll &operator*=(const mod_ll &other) { return *this = *this * other; }
    mod_ll &operator/=(const mod_ll &other) { return *this = *this / other; }
    bool operator==(const mod_ll &other) const { return val == other.val; }
    bool operator!=(const mod_ll &other) const { return val != other.val; }
    friend istream &operator>>(istream &is, mod_ll &m) { return is >> m.val; }
    friend ostream &operator<<(ostream &os, const mod_ll &m) { return os << m.val; }
};

struct segtree {
    ll n;
    vector<mod_ll> evs_squared, evs, variances;
    vector<pair<mod_ll, mod_ll>> lazy;
    segtree(ll n) :
        n(n), evs_squared(n * 4, 0),
        evs(n * 4, 0), variances(n * 4, 0),
        lazy(n * 4, {mod_ll(0), mod_ll(0)}) {}
    void update(ll &lo, ll &hi, mod_ll &ev, mod_ll &variance, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) {
            r = n;
        }
        if (lazy[i] != mp(mod_ll(0), mod_ll(0))) {
            mod_ll ev = lazy[i].first, variance = lazy[i].second;
            evs_squared[i] = evs_squared[i] + ev * ev * (r - l) + evs[i] * ev * 2;
            evs[i] = evs[i] + ev * (r - l);
            variances[i] = variances[i] + variance * (r - l);
            if (r - l > 1) {
                lazy[i * 2] = mp(lazy[i * 2].first + ev, lazy[i * 2].second + variance);
                lazy[i * 2 + 1] = mp(lazy[i * 2 + 1].first + ev, lazy[i * 2 + 1].second + variance);
            }
            lazy[i] = {mod_ll(0), mod_ll(0)};
        }
        if (lo >= r || hi < l) {
            return;
        }
        if (lo <= l && hi >= r - 1) {
            evs_squared[i] = evs_squared[i] + ev * ev * (r - l) + evs[i] * ev * 2;
            evs[i] = evs[i] + ev * (r - l);
            variances[i] = variances[i] + variance * (r - l);
            if (r - l > 1) {
                lazy[i * 2] = mp(lazy[i * 2].first + ev, lazy[i * 2].second + variance);
                lazy[i * 2 + 1] = mp(lazy[i * 2 + 1].first + ev, lazy[i * 2 + 1].second + variance);
            }
            return;
        }
        ll mid = (l + r) / 2;
        update(lo, hi, ev, variance, i * 2, l, mid);
        update(lo, hi, ev, variance, i * 2 + 1, mid, r);
        evs_squared[i] = evs_squared[i * 2] + evs_squared[i * 2 + 1];
        evs[i] = evs[i * 2] + evs[i * 2 + 1];
        variances[i] = variances[i * 2] + variances[i * 2 + 1];
    }
    ll query() {
        return (evs_squared[1] + variances[1]).val;
    }
};

int main() {
    ll n, q;
    cin >> n >> q;
    segtree st(n);
    while (q--) {
        ll x;
        cin >> x;
        if (x == 2) {
            cout << st.query() << '\n';
        } else {
            ll lo, hi;
            cin >> lo >> hi;
            lo--, hi--;
            mod_ll ev = ((mod_ll) hi - lo + 1).inv(), variance = ev * ((mod_ll) 1 - ev);
            st.update(lo, hi, ev, variance);
        }
    }
    return 0;
}