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

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
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
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

pair<vector<pll>, ll> init(vector<ll> &a, ll m, ll v) {
    vector<pll> intervals;
    ll cur = 0, lo = 0, i = 0;
    while (i < sz(a)) {
        cur += a[i++];
        if (cur >= v) {
            intervals.pb({lo, i});
            cur = 0;
            lo = i;
            if (sz(intervals) == m) break;
        }
    }
    if (sz(intervals) < m) return {intervals, -1};
    while (i < sz(a)) cur += a[i++];
    return {intervals, cur};
}

void iterate(vector<pll> &intervals, vector<ll> &a, ll m, ll v, ll &ans) {
    ll cur = ans, hi = sz(a) - 1;
    while (sz(intervals)) {
        auto [lo, hii] = intervals.back();
        intervals.pop_back();
        for (ll i = lo; i < hii; i++) cur += a[i];
        ll sum = 0;
        while (sum < v) {
            cur -= a[hi];
            sum += a[hi--];
        }
        ans = max(ans, cur);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m, v, lo; cin >> n >> m >> v;
        vector<ll> a(n);
        FOR (i, n) cin >> a[i];
        auto [intervals, ans] = init(a, m, v);
        if (ans == -1) {
            cout << -1 << '\n';
            continue;
        }
        iterate(intervals, a, m, v, ans);
        cout << ans << '\n';
    }

    return 0;
}