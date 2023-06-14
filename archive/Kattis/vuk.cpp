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

ll dx[] = {0, 0, -1, 1};
ll dy[] = {-1, 1, 0, 0};

constexpr ll INF = 1e18;

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

bool valid(ll &mid, ll &n, ll &m, ll &s, ll &t, vector<vector<ll>> dists, vector<str> &grid) {
    DSU dsu(n * m);
    FOR (i, n) {
        FOR (j, m) {
            if (dists[i][j] >= mid) {
                FOR (k, 4) {
                    ll ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m && dists[ni][nj] >= mid) {
                        dsu.unite(i * m + j, ni * m + nj);
                    }
                }
            }
        }
    }
    return dsu.same_set(s, t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, s, t;
    cin >> n >> m;
    vector<vector<ll>> dists(n, vector<ll>(m, INF));
    queue<pair<ll, ll>> q;
    vector<str> grid(n);
    FOR (i, n) {
        cin >> grid[i];
        FOR (j, m) {
            if (grid[i][j] == 'V') {
                s = i * m + j;
            } elif (grid[i][j] == 'J') {
                t = i * m + j;
            } elif (grid[i][j] == '+') {
                dists[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    while (!q.empty()) {
        ll i = q.front().first, j = q.front().second;
        q.pop();
        FOR (k, 4) {
            ll ni = i + dx[k], nj = j + dy[k];
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && dists[ni][nj] == INF) {
                dists[ni][nj] = dists[i][j] + 1;
                q.push({ni, nj});
            }
        }
    }
    ll lo = 0, hi = 1000;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (valid(mid, n, m, s, t, dists, grid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo << '\n';

    return 0;
}