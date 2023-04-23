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

ll dx[4] = {-1, 0, 1, 0};
ll dy[4] = {0, -1, 0, 1};

struct DSU {
    ll cnt;
    vector<ll> e;
    DSU(ll n) { e = vector<ll>(n, -1); cnt = n; }
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
    ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool same_set(ll a, ll b) { return get(a) == get(b); }
    ll size(ll x) { return -e[get(x)]; }
    ll count() { return cnt; }
    bool unite(ll x, ll y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        cnt--;
        return true;
    }
};

bool valid(ll &mid, ll &k, vector<vector<ll>> &grid) {
    // map<pair<ll, ll>, ll> hashes;
    ll cnt = 0;
    vector<vector<ll>> hashes(sz(grid), vector<ll>(sz(grid[0])));
    FOR (i, sz(grid)) {
        FOR (j, sz(grid[i])) {
            if (grid[i][j] >= mid) {
                // hashes[{i, j}] = sz(hashes);
                hashes[i][j] = cnt++;
            }
        }
    }
    DSU dsu(cnt);
    FOB (i, 1, sz(grid) - 1) {
        FOB (j, 1, sz(grid[i]) - 1) {
            if (grid[i][j] < mid) {
                continue;
            }
            FOR (l, 4) {
                ll ni = i + dx[l];
                ll nj = j + dy[l];
                if (grid[ni][nj] >= mid) {
                    // dsu.unite(hashes[{i, j}], hashes[{ni, nj}]);
                    dsu.unite(hashes[i][j], hashes[ni][nj]);
                }
            }
        }
    }
    if (dsu.cnt != 1) {
        return false;
    }
    vector<ll> sweep(sz(grid[0]));
    for (ll i = sz(grid) - 2; i >= 1; i--) {
        FORE (x, sweep) {
            x--;
        }
        FOB (j, 1, sz(grid[i]) - 1) {
            if (grid[i][j] >= mid) {
                FOB (nj, j - mid + 1, j + 1) {
                    sweep[nj] = mid;
                }
            }
        }
        FOR (j, sz(grid[i])) {
            if (grid[i][j] > 0 && sweep[j] <= 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> grid(n + 2, vector<ll>(m + 2));
    FOR (l, k) {
        ll i, j;
        cin >> i >> j;
        grid[i][j] = -1;
    }
    FOR (i, n + 2) {
        grid[i][0] = -1;
        grid[i][m + 1] = -1;
    }
    FOR (j, m + 2) {
        grid[0][j] = -1;
        grid[n + 1][j] = -1;
    }
    FOB (i, 1, n + 1) {
        FOB (j, 1, m + 1) {
            if (grid[i][j] != 0) {
                continue;
            }
            grid[i][j] = 1 +
                max(0LL,
                min(grid[i - 1][j],
                min(grid[i][j - 1],
                    grid[i - 1][j - 1])));
        }
    }

    // vector<bool> test(max(n, m));
    // FOR (i, sz(test)) {
    //     test[i] = valid(i, k, grid);
    // }

    ll lo = 0, hi = min(n, m);
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;
        if (valid(mid, k, grid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    if (lo == 0) {
        cout << -1 << '\n';
    } else {
        cout << lo << '\n';
    }

    return 0;
}