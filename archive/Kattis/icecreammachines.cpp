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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> c(n);
    FOR (i, n) {
        cin >> c[i];
        c[i]--;
    }
    vector<ll> last_seen(m, n), nxt(n);
    FORR (i, n) {
        nxt[i] = last_seen[c[i]];
        last_seen[c[i]] = i;
    }
    ll rv = 0;
    set<pair<ll, ll>> active;
    vector<bool> in_active(m);
    FOR (i, n) {
        if (in_active[c[i]]) {
            active.erase({i, c[i]});
        } else {
            rv++;
            if (sz(active) == k) {
                auto [pos, col] = *active.rbegin();
                active.erase({pos, col});
                in_active[col] = false;
            }
        }
        in_active[c[i]] = true;
        active.insert({nxt[i], c[i]});
    }
    cout << rv << '\n';

    return 0;
}