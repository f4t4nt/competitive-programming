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

ll MOD = 998244353;

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

struct Seg{
    ll len, first, last;
    bool f1;
};

mll solve_case(ll n, vector<pll> &rules) {
    vector<vector<bool>> invalid(n + 1, vector<bool>(n + 1));
    for (auto [i, x] : rules) invalid[i][x] = true;
    vector<vector<Seg>> segs(n);
    for (ll pos = 0; pos < n; pos++) {
        ll max_len = n - pos;
        for (ll s = 1; s <= max_len; s++) {
            for (ll r = 1; r <= s; r++) {
                bool ok = true;
                for (ll j = 0; j < s && ok; j++) {
                    ll val = ((r - 1 + j) % s) + 1;
                    if (invalid[pos + 1 + j][val]) ok = false;
                }
                if (!ok) continue;
                ll last = (r > 1 ? r - 1 : s);
                segs[pos].pb({ s, r, last, (r == 1) });
            }
        }
    }

    vector<mll> dp0(n + 1);
    vector<vector<mll>> dp1(n + 1, vector<mll>(n + 1));
    dp0[n] = 1;
    fill(all(dp1[n]), 1);
    for (ll pos = n - 1; pos >= 0; pos--) {
        auto &v = segs[pos];
        mll tot = 0;
        for (Seg &sg : v) {
            mll nxt = sg.f1 ? dp1[pos + sg.len][sg.last] : dp0[pos + sg.len];
            tot += nxt;
        }
        dp0[pos] = tot;
        for (ll prv = 1; prv <= n; prv++) {
            mll bad = 0;
            for (Seg &sg : v) {
                if (sg.first == prv + 1) {
                    mll nxt = sg.f1 ? dp1[pos + sg.len][sg.last] : dp0[pos + sg.len];
                    bad += nxt;
                }
            }
            dp1[pos][prv] = tot - bad;
        }
        dp1[pos][0] = dp0[pos];
    }

    return dp0[0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<pll> rules(m);
        for (auto &[i, x] : rules) cin >> i >> x;
        cout << solve_case(n, rules) << '\n';
    }

    return 0;
}
