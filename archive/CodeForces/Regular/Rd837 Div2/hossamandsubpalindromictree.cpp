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

    ll t;
    cin >> t;

    while (t--) {
        ll n;
        cin >> n;
        str s;
        cin >> s;
        vector<pair<ll, ll>> edges(n - 1);
        vector<vector<ll>> adj(n);
        FOR (i, n - 1) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            edges[i] = {a, b};
            adj[a].pb(b);
            adj[b].pb(a);
        }

        vector<vector<ll>> inter(n, vector<ll>(n, -1)), dp(n, vector<ll>(n, 1));
        queue<tuple<ll, ll, ll>> q;
        vector<vector<pair<ll, ll>>> lens(n);

        FOR (i, n) {
            inter[i][i] = i;
            q.push({i, i, 0});
        }

        while (!q.empty()) {
            ll origin, prev, len;
            tie(origin, prev, len) = q.front();
            q.pop();
            lens[len].pb({origin, prev});
            FORE (next, adj[prev]) {
                if (inter[next][origin] == -1) {
                    inter[next][origin] = prev;
                    q.push({origin, next, len + 1});
                }
            }
        }

        FORE (edge, edges) {
            ll a, b;
            tie(a, b) = edge;
            if (s[a] == s[b]) {
                dp[a][b] = 2;
            }
        }

        FOB (len, 2, n) {
            FORE (pair, lens[len]) {
                ll a, b;
                tie(a, b) = pair;
                ll a_in = inter[a][b], b_in = inter[b][a];
                dp[a][b] = max(dp[a_in][b], dp[a][b_in]);
                if (s[a] == s[b]) {
                    dp[a][b] = max(dp[a][b], dp[a_in][b_in] + 2);
                }
            }
        }

        ll rv = 0;
        FOR (i, n) {
            FOR (j, n) {
                rv = max(rv, dp[i][j]);
            }
        }
        cout << rv << '\n';
    }

    return 0;
}