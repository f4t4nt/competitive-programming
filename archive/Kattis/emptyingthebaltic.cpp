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

ll dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
ll dy[] = {1, 0, -1, 1, -1, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll h, w, x, y;
    cin >> h >> w;
    vector<vector<ll>> a(h, vector<ll>(w));
    FOR (i, h) FOR(j, w) {
        cin >> a[i][j];
        a[i][j] = min(a[i][j], 0LL);
    }
    cin >> x >> y;
    x--, y--;
    vector<vector<bool>> vis(h, vector<bool>(w));
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;
    pq.push({a[x][y], x, y});
    while (!pq.empty()) {
        auto [d, i, j] = pq.top();
        pq.pop();
        if (vis[i][j]) {
            continue;
        }
        vis[i][j] = true;
        set<ll> adj_d = {0};
        FOR (k, 8) {
            ll ni = i + dx[k], nj = j + dy[k];
            if (ni >= 0 && ni < h && nj >= 0 && nj < w) {
                if (vis[ni][nj]) {
                    adj_d.insert(a[ni][nj]);
                } else {
                    pq.push({a[ni][nj], ni, nj});
                }
            }
        }
        if (i == x && j == y) {
            continue;
        }
        a[i][j] = max(a[i][j], *adj_d.begin());
    }
    ll rv = 0;
    FOR (i, h) FOR (j, w) {
        rv += a[i][j];
    }
    cout << -rv << '\n';

    return 0;
}