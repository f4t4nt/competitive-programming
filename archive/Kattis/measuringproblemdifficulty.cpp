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

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<vector<ll>> rank(n, vector<ll>(3));
        FOR (i, 3) {
            FOR (j, n) {
                ll x;
                cin >> x;
                x--;
                rank[x][i] = j;
            }
        }
        ssort(rank);
        ll scale = 1;
        while (scale * scale < n) {
            scale++;
        }
        vector<vector<vector<pair<ll, ll>>>> grid(scale,
            vector<vector<pair<ll, ll>>>(scale));
        ll rv = 0;
        FOR (i, n) {
            ll a = rank[i][0], b = rank[i][1], c = rank[i][2];
            ll x = b / scale, y = c / scale;
            grid[x][y].pb({b, c});
            FOR (j, x) {
                FOR (k, y) {
                    rv += sz(grid[j][k]);
                }
            }
            FOR (j, x + 1) {
                FORE (p, grid[j][y]) {
                    if (p.first < b && p.second < c) {
                        rv++;
                    }
                }
            }
            FOR (k, y) {
                FORE (p, grid[x][k]) {
                    if (p.first < b && p.second < c) {
                        rv++;
                    }
                }
            }
        }
        cout << rv << '\n';
    }

    return 0;
}