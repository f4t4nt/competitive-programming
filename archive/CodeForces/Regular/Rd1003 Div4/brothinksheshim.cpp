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
#define sz(C) (ll)C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

struct BIT {
    vector<mll> tree; ll n;
    BIT(ll n) : n(n) { tree.resize(n + 1); }
    void upd(ll idx, mll val) {
        idx++;
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }
    mll qry(ll idx) {
        idx++; mll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
    mll qry(ll l, ll r) { // [l, r]
        return qry(r) - qry(l - 1);
    }
};
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    vector<mll> pow2(2e5 + 1, 1);
    for (ll i = 0; i < 2e5; i++)
        pow2[i + 1] = 2 * pow2[i];
    
    ll t; cin >> t;
    while (t--) {
        str s; cin >> s;
        ll n = sz(s), q;
        bitset<200000> b;
        for (ll i = 0; i < n; i++)
            b[i] = s[i] - '0';
        cin >> q;
        mll ans = pow2[n] - 1;
        vector<BIT> fwd(2, BIT(n + 1)), bwd = fwd;
        {
            mll cnt[2] = {0, 0};
            ll i = 0, j = n - 1;
            while (i < n) {
                fwd[b[i]].upd(i, pow2[i]);
                bwd[b[i]].upd(i, pow2[j]);
                cnt[b[i]] += pow2[i];
                ans += cnt[b[i] ^ 1] * pow2[j];
                i++, j--;
            }
        }
        while (q--) {
            ll i; cin >> i; i--;
            ans -= fwd[!b[i]].qry(0, i) * pow2[n - i - 1]
                + bwd[!b[i]].qry(i, n - 1) * pow2[i];
            fwd[b[i]].upd(i, -pow2[i]);
            bwd[b[i]].upd(i, -pow2[n - i - 1]);
            b[i] = !b[i];
            ans += fwd[!b[i]].qry(0, i) * pow2[n - i - 1]
                + bwd[!b[i]].qry(i, n - 1) * pow2[i];
            fwd[b[i]].upd(i, pow2[i]);
            bwd[b[i]].upd(i, pow2[n - i - 1]);
            cout << ans << ' ';
        }
        cout << '\n';
    }
 
    return 0;
}