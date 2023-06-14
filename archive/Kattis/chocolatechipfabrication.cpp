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

ll dx[4] = {1, 0, -1, 0};
ll dy[4] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;
    vector<str> grid(n);
    vector<vector<ll>> dist(n + 2, vector<ll>(m + 2, 1e18));
    FOR (i, n) {
        cin >> grid[i];
    }
    dist[0][0] = 0;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        ll x, y, d;
        tie(d, x, y) = pq.top();
        pq.pop();
        if (d > dist[x][y]) {
            continue;
        }
        FOR (i, 4) {
            ll nx = x + dx[i];
            ll ny = y + dy[i];
            if (nx < 0 || nx >= n + 2 || ny < 0 || ny >= m + 2) {
                continue;
            }
            ll nd;
            if (nx == 0 || nx == n + 1 || ny == 0 || ny == m + 1 || grid[nx - 1][ny - 1] == '-') {
                nd = 0;
            } elif (grid[nx - 1][ny - 1] == 'X') {
                nd = d + 1;
            }
            if (nd < dist[nx][ny]) {
                dist[nx][ny] = nd;
                pq.push({nd, nx, ny});
            }
        }
    }

    ll rv = 0;
    FOR (i, n + 2) {
        FOR (j, m + 2) {
            rv = max(rv, dist[i][j]);
            // cout << dist[i][j] << ' ';
        }
        // cout << '\n';
    }
    cout << rv << '\n';

    return 0;
}