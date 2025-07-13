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

struct Line {
    ll m, b; // y = mx + b
    ll value_at(ll x) const {
        return m * x + b;
    }
};

bool bad(const Line &l1, const Line &l2, const Line &l3) {
    return (l3.b - l1.b) * (l2.m - l1.m) >= (l2.b - l1.b) * (l3.m - l1.m);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, x0; cin >> n >> x0;
    vector<ll> s(n), f(n), dp(n);
    for (ll &x : s) cin >> x;
    for (ll &x : f) cin >> x;
    deque<Line> hull;
    hull.pb({x0, 0});
    for (ll i = 0; i < n; i++) {
        while (sz(hull) >= 2 &&
            hull[0].value_at(s[i]) >= hull[1].value_at(s[i]))
        { hull.pop_front(); }
        dp[i] = hull[0].value_at(s[i]);
        Line cur = {f[i], dp[i]};
        while (sz(hull) >= 2 &&
            bad(hull[sz(hull) - 2], hull[sz(hull) - 1], cur))
        { hull.pop_back(); }
        hull.pb(cur);
    }
    cout << dp[n - 1] << '\n';

    return 0;
}
