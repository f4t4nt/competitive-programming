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

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// struct BIT {
//     vector<ll> tree; ll n;
//     BIT(ll n) : n(n), tree(n + 1, 0) {}
//     void upd(ll idx, ll x) {
//         while (idx <= n) {
//             tree[idx] = max(tree[idx], x);
//             idx |= idx + 1;
//         }
//     }
//     ll qry(ll idx) {
//         ll x = 0;
//         while (idx > 0) {
//             x = max(x, tree[idx - 1]);
//             idx &= idx - 1;
//         }
//         return x;
//     }
// };

struct BIT {
    vector<ll> tree; ll n;
    BIT(ll n) : n(n) { tree.resize(n + 1); }
    void upd(ll idx, ll val) {
        idx++;
        while (idx <= n)
        { tree[idx] = max(tree[idx], val); idx += idx & (-idx); }
    }
    ll qry(ll idx) {
        idx++; ll mx = 0;
        while (idx > 0)
        { mx = max(tree[idx], mx); idx -= idx & (-idx); }
        return mx;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k; cin >> n >> k;
    vector<ll> deck1(n * k), deck2 = deck1;
    FOR (i, n * k) {
        cin >> deck1[i];
        deck1[i]--;
    }
    FOR (i, n * k) {
        cin >> deck2[i];
        deck2[i]--;
    }
    vector<vector<ll>> idxs(n);
    FORR (i, n * k) {
        idxs[deck2[i]].pb(i);
    }

    ll ans = 0;
    BIT bit(n * k + 1);

    for (ll a : deck1) {
        for (ll j : idxs[a]) {
            ll x = bit.qry(j) + 1;
            bit.upd(j + 1, x);
            ans = max(ans, x);
            // FOR (i, n * k) cout << setw(3) << bit.qry(i);
            // cout << '\n';
        }
    }

    cout << ans << '\n';

    return 0;
}