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

struct BIT {
    vector<ll> tree; ll n;
    BIT(ll n) : n(n) { tree.resize(n + 1); }
    void update(ll idx, ll val) {
        idx++;
        while (idx <= n)
        { tree[idx] += val; idx += idx & (-idx); }
    }
    ll query(ll idx) {
        idx++; ll sum = 0;
        while (idx > 0)
        { sum += tree[idx]; idx -= idx & (-idx); }
        return sum;
    }
    ll query(ll l, ll r) { return query(r) - query(l - 1); }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, q; cin >> n >> q;
        BIT bit(n + q + 1);
        vector<ll> pos(n);
        FOR (i, n) {
            pos[i] = n - i - 1;
            bit.update(i, 1);
        }
        ll cur = n;
        FOR (_, q) {
            ll x; cin >> x; x--;
            bit.update(pos[x], -1);
            cout << bit.query(pos[x], n + q) << ' ';
            pos[x] = cur++;
            bit.update(pos[x], 1);
        }
        cout << '\n';
    }

    return 0;
}