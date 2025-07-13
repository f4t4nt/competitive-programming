#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 1e9 + 7;

struct mll {
    ll v;
    mll(): v(0) {}
    mll(ll _v) { v = (_v % MOD + MOD) % MOD; }
    explicit operator ll() const { return v; }
    mll& operator+=(const mll &o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    mll& operator-=(const mll &o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    mll& operator*=(const mll &o) { v = (ll)(v * o.v % MOD); return *this; }
    mll& operator/=(const mll &o) { return *this *= o.inv(); }
    friend mll operator+(mll a, const mll &b) { return a += b; }
    friend mll operator-(mll a, const mll &b) { return a -= b; }
    friend mll operator*(mll a, const mll &b) { return a *= b; }
    friend mll operator/(mll a, const mll &b) { return a /= b; }
    mll operator-() const { return mll(-v); }
    bool operator==(const mll &o) const { return v == o.v; }
    bool operator!=(const mll &o) const { return v != o.v; }
    static mll pow(mll a, ll e) {
        mll r = 1;
        while (e > 0) {
            if (e & 1) r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }
    mll inv() const { return pow(*this, MOD - 2); }
    friend ostream& operator<<(ostream &os, const mll &m) { return os << m.v; }
    friend istream& operator>>(istream &is, mll &m) { ll x; is >> x; m = mll(x); return is; }
};

vector<ll> prefix_function(str &s) {
    ll n = sz(s);
    vector<ll> pi(n);
    for (ll i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<vector<ll>> build_adj(str &s) {
    ll m = sz(s);
    auto pi = prefix_function(s);
    vector<vector<ll>> nxt(m, vector<ll>(26));
    for (ll c = 0; c < 26; c++)
        nxt[0][c] = (s[0] == 'A' + c) ? 1 : 0;
    for (ll i = 1; i < m; i++) {
        for (ll c = 0; c < 26; c++) {
            if (s[i] == 'A' + c) nxt[i][c] = i + 1;
            else nxt[i][c] = nxt[pi[i - 1]][c];
        }
    }
    vector<vector<ll>> adj(m, vector<ll>(m, 0));
    for (ll i = 0; i < m; i++) {
        for (ll c = 0; c < 26; c++) {
            ll to = nxt[i][c];
            if (to == m) continue;
            adj[i][to]++;
        }
    }
    return adj;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    str s; cin >> s;
    ll m = sz(s);
    vector<mll> dp0(m);
    dp0[0] = 1;
    auto adj = build_adj(s);
    for (ll i = 0; i < n; i++) {
        vector<mll> dp1(m);
        for (ll j = 0; j < m; j++) {
            for (ll k = 0; k < m; k++) {
                dp1[k] += dp0[j] * adj[j][k];
            }
        }
        dp0 = dp1;
    }
    mll ans = mll::pow(mll(26), n);
    for (mll x : dp0) ans -= x; 
    cout << ans << '\n';

    return 0;
}
