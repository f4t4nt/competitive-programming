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

bitset<1000> shift_left(bitset<1000> cur, bitset<1000> mask, ll n, ll d) {
    bitset<1000> res = (cur >> d) & mask;
    res |= (cur << (n - d)) & mask;
    return res;
}

bitset<1000> shift_right(bitset<1000> cur, bitset<1000> mask, ll n, ll d) {
    bitset<1000> res = (cur << d) & mask;
    res |= (cur >> (n - d)) & mask;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    bitset<1000> cur, mask;
    while (t--) {
        ll n, m, x; cin >> n >> m >> x; x--;
        cur.reset();
        cur[x] = 1;
        mask.reset();
        FOR (i, n) mask[i] = 1;
        FOR (_, m) {
            ll d; cin >> d;
            ch dir; cin >> dir;
            bitset<1000> nxt;
            if (dir == '?') {
                nxt = shift_left(cur, mask, n, d) | shift_right(cur, mask, n, d);
            } elif (dir == '1') {
                nxt = shift_left(cur, mask, n, d);
            } else {
                nxt = shift_right(cur, mask, n, d);
            }
            cur = nxt;
        }
        cout << cur.count() << '\n';
        FOR (i, n) if (cur[i]) cout << i + 1 << ' ';
        cout << '\n';
    }

    return 0;
}