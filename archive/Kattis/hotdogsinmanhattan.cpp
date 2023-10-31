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

ll dx[] = {1, 0, -1, 0},
   dy[] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, w, h;
        cin >> n >> w >> h;
        vector<vector<ll>> dist(w, vector<ll>(h, 1e18));
        std::priority_queue<pair<ll, pair<ll, ll>>, vector<pair<ll, pair<ll, ll>>>, greater<>> pq;
        FOR (i, n) {
            ll x, y;
            cin >> x >> y;
            dist[x][y] = 0;
            pq.push({0, {x, y}});
        }
        while (!pq.empty()) {
            auto [d, p] = pq.top();
            pq.pop();
            auto [x, y] = p;
            if (d > dist[x][y]) continue;
            FOR (i, 4) {
                ll nx = x + dx[i], ny = y + dy[i];
                if (nx >= 0 && nx < w && ny >= 0 && ny < h) {
                    if (dist[nx][ny] > dist[x][y] + 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        pq.push({dist[nx][ny], {nx, ny}});
                    }
                }
            }
        }
        ll lo = 0, hi = w + h - 2;
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            vector<ll> mn(h, 1e18), mx(h, -1e18);
            FOR (x, w) {
                FOR (y, h) {
                    if (dist[x][y] >= mid) {
                        mn[y] = min(mn[y], x);
                        mx[y] = max(mx[y], x);
                    }
                }
            }
            bool ok = false;
            FOR (y0, h) {
                FOR (y1, h) {
                    if (mn[y0] != 1e18 && mx[y1] != -1e18 &&
                        abs(mn[y0] - mx[y1]) + abs(y1 - y0) >= mid)
                    {
                        ok = true;
                        break;
                    }
                }
                if (ok) break;
            }
            if (ok) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        cout << lo << '\n';
    }

    return 0;
}