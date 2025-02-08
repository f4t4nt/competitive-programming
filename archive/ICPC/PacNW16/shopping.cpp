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
#define f first
#define s second

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

ll MAXN = 20;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<ll> a(n + 1);
    FOR (i, n) cin >> a[i];
    vector<vector<ll>> ref(MAXN, vector<ll>(n + 1, n));
    stack<pll> stk;
    stk.push({0, n});
    FORR (i, n) {
        while (stk.top().f >= a[i]) stk.pop();
        ref[0][i] = stk.top().s;
        stk.push({a[i], i});
    }
    FOR1 (i, MAXN) FOR (j, n) ref[i][j] = ref[i - 1][ref[i - 1][j]];
    while (q--) {
        ll x, l, r; cin >> x >> l >> r;
        l--, r--;
        while (x && l <= r) {
            x %= a[l];
            FORR (i, MAXN) if (a[ref[i][l]] > x) l = ref[i][l];
            l++;
        }
        cout << x << '\n';
    }

    return 0;
}