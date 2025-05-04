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

template<typename T> using indexed_set = tree<
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
        ll n, cnt0 = 0; cin >> n;
        vector<ll> a(n), aa;
        for (ll i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] || (a[i] == 0 && cnt0++ == 0))
                aa.pb(a[i]);
        }
        if (cnt0 == 0) {
            cout << n << '\n';
            continue;
        }
        vector<ll> pre_min(n), suf_mex(n);
        vector<bool> vis(n + 1);
        pre_min[0] = a[0];
        for (ll i = 1; i < n; i++) {
            pre_min[i] = min(pre_min[i - 1], a[i]);
        }
        ll mex = 0;
        n = sz(aa);
        for (ll i = n - 1; i >= 0; i--) {
            if (aa[i] <= n) {
                vis[aa[i]] = true;
                while (vis[mex]) mex++;
            }
            suf_mex[i] = mex;
        }
        bool ok = true;
        for (ll i = 1; i < n; i++) {
            if (pre_min[i - 1] < suf_mex[i]) {
                ok = false;
                break;
            }
        }
        cout << (ok ? n : n - 1) << '\n';
    }

    return 0;
}