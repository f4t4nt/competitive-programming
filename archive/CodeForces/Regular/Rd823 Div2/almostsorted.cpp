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

template<class T>
struct Fenwick {
    ll n;               // logical length (0-indexed externally)
    vector<T> bit;      // 1-based internal tree
    T def_val;          // neutral (usually 0 for +)

    // helpers
    static void combine(T &a, const T &b) { a += b; }               // point-update
    static T    prefix_op(const T &a, const T &b) { return a + b; } // query merge
    static T    inverse (const T &x) { return -x; }                 // for range

    // constructor
    Fenwick(ll _n,
            T _def_val = T{})                   // neutral element
        : n(_n),
          bit(n + 1, _def_val),
          def_val(_def_val) {}

    // point add (a[i] += delta)
    void upd(ll idx, const T &delta) {          // 0-based idx
        for (idx++; idx <= n; idx += idx & -idx)
            combine(bit[idx], delta);
    }

    // prefix sum (inclusive)
    T pref(ll idx) const {                      // 0-based idx
        T res = def_val;
        for (idx++; idx > 0; idx -= idx & -idx)
            res = prefix_op(res, bit[idx]);
        return res;
    }

    // range query [l, r] (inclusive)
    T qry(ll l, ll r) const {
        if (l > r) return def_val;
        return prefix_op(pref(r),
               prefix_op(inverse(pref(l - 1)), def_val));
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k; cin >> n >> k;
    vector<ll> a(n), pos(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        pos[a[i]] = i;
    }
    Fenwick<ll> bit(n);

    auto eval = [&](ll mn, ll mask, ll x) -> ll {
        ll res = 0;
        for (ll i = 0; i < k; i++)
            if (mask & (1 << i) && pos[x] < pos[mn + 1 + i])
                res++;
        res += bit.qry(pos[x], n - 1);
        return res;
    };

    vector<vector<ll>> dp(n + 1, vector<ll>(1 << k, 1e18));
    dp[0][0] = 0;
    for (ll mn = 0; mn < n; mn++) {
        ll k2 = min(k, n - mn - 1);
        for (ll mask = 0; mask < (1 << k2); mask++) {
            for (ll i = 0; i < k2; i++)
                if ((mask & (1 << i)) == 0)
                    dp[mn][mask | (1 << i)] = min(dp[mn][mask | (1 << i)], dp[mn][mask] + eval(mn, mask, mn + 1 + i));
            ll mn2 = mn + 1, mask2 = mask;
            while (mask2 & 1) {
                mn2++;
                mask2 >>= 1;
            }
            mask2 >>= 1;
            dp[mn2][mask2] = min(dp[mn2][mask2], dp[mn][mask] + eval(mn, mask, mn));
        }
        bit.upd(pos[mn], 1);
    }
    cout << dp[n][0] << '\n';

    return 0;
}
