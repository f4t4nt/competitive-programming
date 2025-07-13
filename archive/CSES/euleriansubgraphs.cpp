#include <bits/stdc++.h>
using namespace std;

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
#define x first
#define y second

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < m; i++) {
        ll u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<bool> vis(n);
    ll components = 0;
    auto dfs = [&](auto self, ll v) -> void {
        vis[v] = true;
        for (ll to : adj[v]) {
            if (!vis[to]) self(self, to);
        }
    };
    for (ll v = 0; v < n; v++)
        if (!vis[v]) {
            dfs(dfs, v);
            components++;
        }
    cout << mll::pow(2, m - n + components) << '\n';

    return 0;
}
