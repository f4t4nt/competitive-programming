#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
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

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 998244353;
const ll MAXN = 5e5 + 1;

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

struct NumTheory {
    ll N;
    vector<mll> fac, ifac, inv;
    vector<mll> catalan;

    NumTheory(ll _N): N(_N),
        fac(N + 1), ifac(N + 1), inv(N + 1),
        catalan(N + 1)
    {
        // factorial / inverse factorial / inverse
        fac[0] = 1;
        for (ll i = 1; i <= N; i++) fac[i] = fac[i - 1] * mll(i);
        ifac[N] = fac[N].inv();
        for (ll i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * mll(i);
        for (ll i = 1; i <= N; i++) inv[i] = ifac[i] * fac[i - 1];

        // Catalan numbers
        catalan[0] = 1;
        for (ll n = 1; n <= N / 2; n++)
            catalan[n] = choose(2 * n, n) / mll(n + 1);
    }

    mll choose(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] * ifac[n-k];
    }
};

struct Segment {
    ll l, r, id;
    bool operator<(const Segment& o) const {
        if (l != o.l) return l < o.l;
        return r > o.r;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    NumTheory nt(MAXN);
    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<Segment> segs;
        set<pll> seen;
        ll id = 0;
        for (ll i = 0; i < m; i++) {
            ll l, r; cin >> l >> r;
            segs.pb({l, r, id++});
            seen.insert({l, r});
        }
        for (ll i = 1; i <= n; i++)
            if (!seen.count({i, i}))
                segs.pb({i, i, id++});
        if (!seen.count({1, n}))
            segs.pb({1, n, id++});

        ssort(segs);
        vector<vector<ll>> adj(id);
        vector<ll> par(id, -1);
        stack<Segment> stk;
        for (const auto& seg : segs) {
            while (!stk.empty() && !(stk.top().l <= seg.l && seg.r <= stk.top().r)) {
                stk.pop();
            }
            if (!stk.empty()) {
                par[seg.id] = stk.top().id;
                adj[stk.top().id].pb(seg.id);
            }
            stk.push(seg);
        }

        mll ans = 1;
        for (ll i = 0; i < id; i++) {
            ll c = sz(adj[i]);
            if (c >= 2) ans *= nt.catalan[c - 1];
        }
        cout << ans << '\n';
    }

    return 0;
}
