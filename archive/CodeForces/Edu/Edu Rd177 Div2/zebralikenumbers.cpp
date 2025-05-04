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

const ll INF = 1e18;

vector<ll> zebra;
map<pll, ll> mem;

ll f(ll m, ll k) {
    if (m < 1) return 0;
    if (m < 5) return k >= 1 && k <= m;
    if (k == 0) return 0;
    pll key = {m, k};
    if (mem.count(key)) return mem[key];
    ll tot = 0;
    for (ll i = 0; i < sz(zebra); i++) {
        if (zebra[i] > m) break;
        ll lo = zebra[i],
            hi = (i + 1 < sz(zebra) ? min(m, zebra[i + 1] - 1) : m),
            range = hi - lo,
            contrib = 0;
        if (k == 1) contrib += 1;
        if (k > 1 && range >= 1) contrib += f(range, k - 1);
        tot += contrib;
    }
    return mem[key] = tot;
}

ll cnt(ll x, ll k) {
    if (x < 1) return 0;
    return f(x, k);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll x = 1;
    while (true) {
        if (x > 4 * INF) break;
        zebra.pb(x);
        x = 4 * x + 1;
    }
    
    ll t; cin >> t;
    while (t--) {
        ll l, r, k; cin >> l >> r >> k;
        cout << cnt(r, k) - cnt(l - 1, k) << '\n';
    }
    
    return 0;
}