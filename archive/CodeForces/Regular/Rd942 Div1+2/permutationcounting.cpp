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
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool ok(vector<ll> &a, ll mid, ll k) {
    ll tot = 0;
    FOR (i, sz(a)) tot += max(0LL, mid - a[i]);
    return tot <= k;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        vector<ll> a(n);
        FOR (i, n) cin >> a[i];
        ll lo = *min_element(all(a)), hi = 1e13;
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            if (ok(a, mid, k)) lo = mid;
            else hi = mid - 1;
        }
        FORE (x, a) if (x < lo) {
            k -= lo - x;
            x = lo;
        }
        ll cnt = 0;
        FOR (i, n) {
            if (a[i] == lo && k > 0) {
                k--;
                a[i]++;
            }
            if (a[i] > lo) cnt++;
        }
        assert(k == 0);
        assert(cnt < n);
        ll ans = lo * n - n + 1 + cnt;
        cout << max(0LL, ans) << '\n';
    }

    return 0;
}