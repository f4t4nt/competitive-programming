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

    ld h, w, a, b, rv, total = 0, prec = 2e3;
    cin >> h >> w >> a >> b;
    vector<vector<ld>> grid(h + 1, vector<ld>(w + 1));
    FOR (i, h) {
        FOR (j, w) {
            cin >> grid[i + 1][j + 1];
        }
    }
    FOR (i, h) {
        FOR (j, w) {
            grid[i + 1][j + 1] += grid[i + 1][j] + grid[i][j + 1] - grid[i][j];
        }
    }
    vector<ld> bins(1e4 * prec);
    FOB (recth, 1, h + 1) {
        FOB (rectw, 1, w + 1) {
            ld area = recth * rectw;
            if (area > b || area < a) {
                continue;
            }
            FOR (x, h - recth + 1) {
                FOR (y, w - rectw + 1) {
                    ld cnt = grid[x + recth][y + rectw] - grid[x][y + rectw] - grid[x + recth][y] + grid[x][y];
                    cnt /= area;
                    cnt *= prec;
                    bins[(ll) cnt]++;
                    total++;
                }
            }
        }
    }
    FOB (i, 1, sz(bins)) {
        bins[i] += bins[i - 1];
    }
    ll lo0 = 0, hi0 = sz(bins) - 1, lo1 = 0, hi1 = sz(bins) - 1;
    while (lo0 < hi0) {
        ll mid0 = (lo0 + hi0) / 2, mid1 = (lo1 + hi1) / 2;
        if (bins[mid0] < total / 2) {
            lo0 = mid0 + 1;
        } else {
            hi0 = mid0;
        }
        if (bins[mid1] <= total / 2) {
            lo1 = mid1 + 1;
        } else {
            hi1 = mid1;
        }
    }
    rv = (ld) (lo0 + lo1) / 2 / prec;
    cout << fixed << setprecision(10) << rv << '\n';

    return 0;
}