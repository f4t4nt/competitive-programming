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
    ll,
    null_type,
    less<ll>,
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
        vector<ll> a(n);
        for (ll &ai : a) cin >> ai;
        ll cnt = 0, lo = 0, hi = n - 1;
        for (ll i = 1; i < n; i++)
            if (a[i - 1] > a[i])
                cnt++;
        ll ans = (cnt + 1) / 2;
        if (cnt == 0) {
            cout << 0 << '\n';
            continue;
        }
        while (a[lo] < a[lo + 1]) lo++;
        while (a[hi] > a[hi - 1]) hi--;
        if (cnt % 2 == 0 && a[hi] - a[lo] < hi - lo) ans++;
        cout << ans << '\n';
    }

    return 0;
}