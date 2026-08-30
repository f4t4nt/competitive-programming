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
        ll sqrtn = sqrt(n) + 1, ans = 0;
        vector<ll> a(n);
        for (ll &x : a) cin >> x;
        for (ll j = 0; j < n; j++) {
            ll y = a[j];
            ll lim = min(sqrtn, (n - 1) / y); // need x*y <= (n-1) since j-i <= n-1
            for (ll x = 1; x <= lim; x++) {
                ll i = j - x * y;
                if (i >= 0 && a[i] == x) {
                    ans++;
                }
            }
        }
        for (ll i = 0; i < n; i++) {
            ll x = a[i];
            if (x <= sqrtn || x > n - 1) continue;
            ll lim = (n - 1) / x;
            for (ll y = 1; y <= lim; y++) {
                ll j = i + x * y;
                if (j < n && a[j] == y) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}