#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, k;
    cin >> n >> k;

    vector<set<pair<ll, ll>>> coords(k);
    vector<vector<ll>> dist(n, vector<ll>(n));
    FOR (i, n) {
        FOR (j, n) {
            ll x;
            cin >> x;
            coords[x - 1].insert({i, j});
            if (x == 1) {
                dist[i][j] = 0;
            }
        }
    }

    bool valid = true;
    FOR (i, k) {
        if (sz(coords[i]) == 0) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        cout << -1 << '\n';
        return 0;
    }

    FOB (x, 1, k) {
        FORE (coord, coords[x]) {
            ll min_dist = 1e18;
            FORE (prev_coord, coords[x - 1]) {
                min_dist = min(min_dist, abs(coord.first - prev_coord.first)
                    + abs(coord.second - prev_coord.second)
                    + dist[prev_coord.first][prev_coord.second]);
            }
            dist[coord.first][coord.second] = min_dist;
        }
    }

    ll rv = 1e18;
    FORE (coord, coords[k - 1]) {
        rv = min(rv, dist[coord.first][coord.second]);
    }
    cout << rv << '\n';
    
    return 0;
}