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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n), pre_mx(n + 1), pre_sum(n + 1, 0);
        for (ll i = 0; i < n; ++i) {
            cin >> a[i];
            pre_sum[i + 1] = pre_sum[i] + a[i];
            pre_mx[i + 1] = max(pre_mx[i], a[i]);
        }
        ll tot = pre_sum[n];
        vector<ll> ans(n);
        for (ll k = 1; k <= n; ++k) {
            ll idx = n - k,
                sk = tot - pre_sum[idx],
                delta = 0;
            if (idx > 0) {
                ll best = pre_mx[idx];
                delta = max<ll>(0, best - a[idx]);
            }

            ans[k - 1] = sk + delta;
        }
        for (ll x : ans) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}