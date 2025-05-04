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

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> p(n), d(n), ids(n), szs;
        for (ll &pi : p) cin >> pi;
        for (ll &di : d) cin >> di;
        vector<bool> vis(n);
        ll id = 0;
        for (ll i = 0; i < n; i++) {
            if (!vis[i]) {
                ll cur = i;
                vector<ll> curCycle;
                while (!vis[cur]) {
                    vis[cur] = true;
                    curCycle.pb(cur);
                    cur = p[cur] - 1;
                }
                for (ll index : curCycle) ids[index] = id;
                szs.pb(sz(curCycle));
                id++;
            }
        }
        vector<ll> intact(id, true), ans(n), rem(n);
        ll sum = n;
        for (ll i = 0; i < n; i++) {
            ll pos = d[i] - 1;
            rem[pos] = true;
            ll cId = ids[pos];
            if (cId != -1 && intact[cId]) {
                intact[cId] = false;
                sum -= szs[cId];
            }
            ll operations = n - sum;
            ans[i] = operations;
        }
        for (ll &ai : ans) cout << ai << ' ';
        cout << '\n';
    }

    return 0;
}