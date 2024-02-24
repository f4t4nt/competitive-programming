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
#define x first
#define y second

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

// ll lis(vector<pll> conv) {
//     vector<pll> cur;
//     FORE (card, conv) {
//         if (sz(cur) == 0) cur.pb(card);
//         else {
//             auto it = upper_bound(all(cur), card);
//             if (it == cur.end()) cur.pb(card);
//             else *it = min(*it, card);
//         }
//     }
//     return sz(cur);
// }

const ll INF = 1e18;

vector<ll> lis(vector<ll> a) {
    ll n = sz(a);
    vector<ll> d(n + 1, INF), p(n + 1);
    d[0] = -INF;
    FOR (i, n) {
        ll j = upper_bound(all(d), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            p[i] = j;
        }
    }
    ll len = 0;
    FOR (i, n + 1) if (d[i] < INF) len = i;
    vector<ll> ans(len);
    ll cur = INF;
    FORR (i, n) if (p[i] == len) {
        ans[--len] = a[i];
        cur = a[i];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n;
    while (cin >> n) {
        vector<ll> a(n);
        FOR (i, n) cin >> a[i];
        auto ans = lis(a);
        vector<ll> idxs;
        ll cur = 0;
        FOR (i, sz(ans)) {
            while (a[cur] != ans[i]) cur++;
            idxs.pb(cur);
            cur++;
        }
        cout << sz(ans) << '\n';
        FORE (idx, idxs) cout << idx << ' ';
        cout << '\n';
    }

    return 0;
}