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
#define f first
#define s second

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m, s, p, q;
    cin >> n >> m >> s >> p >> q;
    ll c = (n + m - 1) / m;
    vector<bitset<1000>> pgs0(c), pgs1(c);
    FOR (i, p) {
        ll x; cin >> x; x--;
        pgs0[x / m][x % m] = 1;
    }
    FOR (i, q) {
        ll x; cin >> x; x--;
        pgs1[x / m][x % m] = 1;
    }
    s--;
    ll mn = s, mx = s;
    FOR (i, c) {
        if (pgs0[i] != pgs1[i]) {
            mn = min(mn, i);
            mx = max(mx, i);
        }
    }
    ll ops = mx - mn + min(s - mn, mx - s);
    FOB (i, mn, mx + 1) {
        ll cnt = (i == c - 1 && n % m != 0 ? n % m : m);
        ll cur = min({
            (ll) (pgs1[i].count() + 1),
            (ll) (cnt - pgs1[i].count() + 1),
            (ll) (pgs0[i] ^ pgs1[i]).count()
        });
        ops += cur;
    }
    cout << ops << '\n';

    return 0;
}