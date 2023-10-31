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

// imma show YOU how great i am.

ll dx[] = {0, 0, 1, -1};
ll dy[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k, h;
    cin >> n >> k >> h;
    vector<vector<ll>> heights(n, vector<ll>(n));
    FOR (i, n) {
        FOR (j, n) {
            cin >> heights[i][j];
        }
    }
    vector<vector<bitset<100>>> cur(n, vector<bitset<100>>(n));
    FOR (i, k) {
        ll r, c;
        cin >> r >> c;
        cur[r][c][i] = 1;
    }
    FOR (i, h) {
        ll lvl;
        cin >> lvl;
        auto nxt = cur;
        FOR (i, n) {
            FOR (j, n) {
                FOR (k, 4) {
                    ll x = i + dx[k];
                    ll y = j + dy[k];
                    if (x >= 0 && x < n && y >= 0 && y < n) {
                        nxt[x][y] |= cur[i][j];
                    }
                }
            }
        }
        FOR (i, n) {
            FOR (j, n) {
                if (heights[i][j] <= lvl) {
                    nxt[i][j].reset();
                }
            }
        }
        vector<ll> cnt(k);
        FOR (i, n) {
            FOR (j, n) {
                FOR (l, k) {
                    if (nxt[i][j][l]) {
                        cnt[l]++;
                    }
                }
            }
        }
        bitset<100> ok;
        FOR (i, n) {
            FOR (j, n) {
                // pair<ll, ll> best = {1e18, -1};
                ll freq = 1e18;
                vector<ll> best;
                FOR (l, k) {
                    if (!ok[l] && nxt[i][j][l]) {
                        if (cnt[l] < freq) {
                            freq = cnt[l];
                            best.clear();
                            best.pb(l);
                        } else if (cnt[l] == freq) {
                            best.pb(l);
                        }
                    }
                }
                if (sz(best)) {
                    ll idx = (rand() + 2) % sz(best);
                    ok[best[idx]] = 1;
                    nxt[i][j].reset();
                    nxt[i][j][best[idx]] = 1;
                }
            }
        }
        cur = nxt;
    }
    bitset<100> rv;
    FOR (i, n) {
        FOR (j, n) {
            rv |= cur[i][j];
        }
    }
    cout << rv.count() << '\n';

    return 0;
}