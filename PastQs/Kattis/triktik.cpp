#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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
    vector<pair<ll, ll>> x(n + 1);
    x[0] = {0, 0};
    n++;
    FOB (i, 1, n) {
        cin >> x[i].first;
        x[i].second = i;
        x[i].first *= 2;
    }
    ssort(x);

    ll max_j = 30;
    vector<ll> max_visible(n);
    vector<vector<vector<pair<ll, ll>>>> adj(n, vector<vector<pair<ll, ll>>>(max_j + 1));
    FOR (i, n) {
        FOR (j, max_j) {
            adj[i][j + 1].pb({i, j});
            adj[i][j].pb({i, j + 1});
        }
    }

    FOB (j, 1, max_j + 1) {
        ll span = 1 << j;
        ll lo = 0, curr = 0, hi = 0;
        set<ll, greater<>> in_span;
        while (curr < n) {
            while (lo < curr && x[curr].first - x[lo].first > span) {
                in_span.erase(x[lo].second);
                lo++;
            }
            while (hi < n && x[hi].first - x[curr].first <= span) {
                in_span.insert(x[hi].second);
                hi++;
            }
            ll i = 0;
            auto it = in_span.begin();
            while (i < k && it != in_span.end()) {
                if (*it != 0) {
                    adj[x[curr].second][j].pb({*it, j});
                    i++;
                }
                if (*it == x[curr].second) {
                    max_visible[x[curr].second] = j;
                }
                it++;
            }
            curr++;
        }
    }

    vector<vector<ll>> dist(n, vector<ll>(max_j + 1, 1e18));
    dist[0][1] = 0;
    queue<pair<ll, ll>> q;
    q.push({0, 1});
    while (!q.empty()) {
        ll u, d;
        tie(u, d) = q.front();
        q.pop();
        FORE (v, adj[u][d]) {
            if (dist[v.first][v.second] > dist[u][d] + 1) {
                dist[v.first][v.second] = dist[u][d] + 1;
                q.push({v.first, v.second});
            }
        }
    }

    vector<ll> rv(n, 1e18);
    FOR (i, n) {
        FOR (j, max_visible[i] + 1) {
            rv[i] = min(rv[i], dist[i][j]);
        }
    }

    FOB (i, 1, n) {
        if (rv[i] == 1e18) {
            cout << -1 << '\n';
        } else {
            cout << rv[i] << '\n';
        }
    }

    return 0;
}