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

constexpr ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, s, t;
    cin >> n >> s >> t;
    vector<bool> ok(n);
    set<ll> unvis;
    vector<set<ll>> in(n), adj(n);
    FOR (i, n) {
        ch c;
        cin >> c;
        ok[i] = c == 'N';
        ll m;
        cin >> m;
        FOR (j, m) {
            ll x;
            cin >> x;
            adj[i].insert(x);
            if (ok[i]) {
                in[x].insert(i);
            }
        }
        if (!ok[i]) {
            unvis.insert(i);
        }
    }
    vector<ll> dist(n, INF);
    dist[t] = 0;
    vector<ll> dp0 = {t}, dp1;
    while (!dp0.empty()) {
        dp1.clear();
        FORE (i, dp0) {
            FORE (j, in[i]) {
                if (dist[j] == INF) {
                    dist[j] = dist[i] + 1;
                    dp1.pb(j);
                }
            }
        }
        FORE (i, dp0) {
            set<ll> vis;
            FORE (j, unvis) {
                if (!adj[j].count(i) && dist[j] == INF) {
                    dist[j] = dist[i] + 1;
                    dp1.pb(j);
                    vis.insert(j);
                }
            }
            FORE (j, vis) {
                unvis.erase(j);
            }
        }
        swap(dp0, dp1);
    }
    if (dist[s] == INF) {
        cout << "impossible\n";
    } else {
        cout << dist[s] << '\n';
    }

    return 0;
}