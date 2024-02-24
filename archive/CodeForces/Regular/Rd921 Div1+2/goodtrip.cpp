#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

const ll MOD = 1e9 + 7;

ll pow(ll x, ll p) {
    x %= MOD;
    ll rv = 1;
    while (p) {
        if (p & 1) rv = (rv * x) % MOD;
        x = (x * x) % MOD; p >>= 1;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t; cin >> t;
    while (t--) {
        ll n, m, k; cin >> n >> m >> k;
        vector<ll> w(m);
        FOR (i, m) {
            ll u, v; cin >> u >> v >> w[i];
        }
        ll d = pow(n * (n - 1) / 2, MOD - 2), rv = 0, cur = 0;
        FOR (i, m) cur = (cur + w[i]) % MOD;
        FOR (i, k) {
            rv = (rv + (cur * d) % MOD) % MOD;
            cur = (cur + (m * d) % MOD) % MOD;
            assert(cur >= 0);
            assert(rv >= 0);
        }
        cout << rv << '\n';
    }

    return 0;
}