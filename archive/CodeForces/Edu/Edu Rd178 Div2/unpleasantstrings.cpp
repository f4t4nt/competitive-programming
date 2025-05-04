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

    ll n, k; cin >> n >> k;
    str s; cin >> s;

    vector<vector<ll>> pos(26);
    for (ll i = 0; i < n; i++)
        pos[s[i] - 'a'].pb(i);

    vector<ll> dist(n + 2, 1), nxt(26, -1);
    for (ll pos = n - 1; pos >= 0; pos--) {
        nxt[s[pos] - 'a'] = pos;
        bool missing = false;
        for (ll c = 0; c < k; c++) {
            if (nxt[c] == -1) {
                missing = true;
                break;
            }
        }
        if (missing) dist[pos] = 1;
        else {
            ll best = 1e18;
            for (ll c = 0; c < k; c++)
                best = min(best, dist[nxt[c] + 1]);
            dist[pos] = 1 + best;
        }
    }

    ll q; cin >> q;
    while (q--) {
        str t; cin >> t;
        ll cur = -1;
        bool ok = true;
        for (char ch : t) {
            auto &v = pos[ch - 'a'];
            auto it = lower_bound(all(v), cur + 1);
            if (it == v.end()) {
                ok = false;
                break;
            }
            cur = *it;
        }
        cout << (ok ? dist[cur + 1] : 0) << '\n';
    }

    return 0;
}