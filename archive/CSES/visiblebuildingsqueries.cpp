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

    ll n, q; cin >> n >> q;
    vector<ll> h(n);
    for (ll &x : h) cin >> x;
    h.pb(1e18), n++;
    vector<vector<ll>> nxt(n, vector<ll>(65 - __builtin_clzll(n), n));
    nxt[n - 1][0] = n - 1;
    stack<ll> stk;
    for (ll i = 0; i < n; i++) {
        while (!stk.empty() && h[stk.top()] < h[i]) {
            nxt[stk.top()][0] = i;
            stk.pop();
        }
        stk.push(i);
    }
    for (ll j = 1; j < sz(nxt[0]); j++) {
        for (ll i = 0; i < n; i++) {
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }
    while (q--) {
        ll l, r; cin >> l >> r;
        l--, r--;
        ll ans = 1;
        for (ll j = sz(nxt[0]) - 1; j >= 0; j--) {
            if (nxt[l][j] <= r) {
                ans += (1LL << j);
                l = nxt[l][j];
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
