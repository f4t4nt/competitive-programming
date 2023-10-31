#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
 
#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// https://open.kattis.com/problems/uniformsubtrees

// imma show YOU how great i am.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    str s;
    cin >> s;
    ll n = sz(s) / 2, cnt = 0;
    vector<vector<ll>> adj(n);
    stack<ll> stk;
    FOR(i, sz(s)) {
        if (s[i] == '(') {
            stk.push(cnt);
            cnt++;
        } else {
            ll u = stk.top();
            stk.pop();
            if (sz(stk)) {
                adj[stk.top()].pb(u);
            }
        }
    }

    vector<ll> siz(n), dep(n);
    auto dfs1 = [&](auto &&self, ll u) -> void {
        siz[u] = 1;
        FORE (v, adj[u]) {
            dep[v] = dep[u] + 1;
            self(self, v);
            siz[u] += siz[v];
        }
    };
    dfs1(dfs1, 0);

    FOR (i, sz(adj)) {
        sort(all(adj[i]), [&](ll a, ll b) {
            return siz[a] > siz[b] || (siz[a] == siz[b] && sz(adj[a]) > sz(adj[b]));
            // return sz(adj[a]) > sz(adj[b]) || (sz(adj[a]) == sz(adj[b]) && siz[a] > siz[b]);
        });
    }

    cnt = 0;
    vector<ll> rv;
    auto dfs2 = [&](auto &&self, ll u) -> void {
        FORE (v, rv) {
            cout << v << ' ';
        }
        cout << 0 << '\n';
        cnt++;
        FOR (i, sz(adj[u])) {
            rv.pb(i + 1);
            self(self, adj[u][i]);
            rv.pop_back();
        }
    };
    dfs2(dfs2, 0);
    // cout << cnt << '\n';

    return 0;
}