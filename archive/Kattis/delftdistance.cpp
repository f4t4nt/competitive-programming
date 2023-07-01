#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ch = char;
using str = string;

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
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll h, w;
    cin >> h >> w;
    vector<str> grid(h);
    FOR (i, h) {
        cin >> grid[i];
    }
    ld arc = M_PI / 4;
    vector<vector<ld>> dist(2 * h + 1, vector<ld>(2 * w + 1, 1e18));
    dist[0][0] = 0;
    FOB (s, 1, 2 * (h + w + 1)) {
        FOR (i, 2 * h + 1) {
            ll j = s - i;
            if (j < 0 || j > 2 * w + 1) {
                continue;
            }
            if (i % 2 == 1 && j % 2 == 1) {
                continue;
            }
            if (i > 0) {
                dist[i][j] = min(dist[i][j], dist[i - 1][j] + 0.5);
            }
            if (j > 0) {
                dist[i][j] = min(dist[i][j], dist[i][j - 1] + 0.5);
            }
            if (i > 0 && j > 0 && grid[(i - 1) / 2][(j - 1) / 2] == 'O') {
                dist[i][j] = min(dist[i][j], dist[i - 1][j - 1] + arc);
            }
        }
    }
    cout << fixed << setprecision(10) << 10 * dist[2 * h][2 * w] << '\n';

    return 0;
}