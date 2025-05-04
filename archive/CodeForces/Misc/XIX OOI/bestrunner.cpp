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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m, t; cin >> n >> m >> t;
    vector<ll> a(n), pre(n + 1), nxt(n, -1), prv(n, -1);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        pre[i + 1] = pre[i] + a[i];
    }
    while (m--) {
        ll i; cin >> i; i--;
        nxt[i] = prv[i] = i;
    }
    for (ll i = 1; i < n; i++)
        if (nxt[i] == -1) nxt[i] = nxt[i - 1];
    for (ll i = n - 2; i >= 0; i--)
        if (prv[i] == -1) prv[i] = prv[i + 1];
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll j = nxt[i];
        if (j != -1) {
            ll rem = t - (pre[i] - pre[j]);
            if (rem >= 0) ans = max(ans, i - j + rem / a[i]);
        }
        j = prv[i];
        if (j != -1) {
            ll rem = t - (pre[j + 1] - pre[i + 1]);
            if (rem >= 0) ans = max(ans, j - i + rem / a[i]);
        }
    }
    cout << ans << '\n';

    return 0;
}