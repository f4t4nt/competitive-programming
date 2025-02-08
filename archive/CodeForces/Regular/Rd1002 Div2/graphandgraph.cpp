#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, s1, s2, m1; cin >> n >> s1 >> s2 >> m1;
        vector<vector<ll>> adj1(n + 1);
        FOR(i, m1) {
            ll a, b; cin >> a >> b;
            adj1[a].pb(b);
            adj1[b].pb(a);
        }
        ll m2; cin >> m2;
        vector<vector<ll>> adj2(n + 1);
        FOR(i, m2) {
            ll a, b; cin >> a >> b;
            adj2[a].pb(b);
            adj2[b].pb(a);
        }
        vector<set<ll>> st1(n + 1), st2(n + 1);
        FOR(i, n + 1) {
            for (ll j : adj1[i]) st1[i].insert(j);
            for (ll j : adj2[i]) st2[i].insert(j);
        }
        vector<ll> degh(n + 1);
        FOR(i, n + 1) {
            for (ll j : st1[i]) {
                if (st2[i].count(j)) degh[i]++;
            }
        }
        if (s1 == s2 && degh[s1] > 0) {
            cout << 0 << '\n';
            continue;
        }
        vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
        dist[s1][s2] = 0;
        typedef tuple<ll, ll, ll> state;
        std::priority_queue<state, vector<state>, greater<state>> pq;
        pq.push({0, s1, s2});
        ll best = INF;
        while (!pq.empty()) {
            auto [cd, v1, v2] = pq.top();
            pq.pop();
            if (cd > dist[v1][v2]) continue;
            if (v1 == v2 && degh[v1] > 0) {
                best = cd;
                break;
            }
            for (ll u1 : adj1[v1]) {
                for (ll u2 : adj2[v2]) {
                    ll nd = cd + abs(u1 - u2);
                    if (nd < dist[u1][u2]) {
                        dist[u1][u2] = nd;
                        pq.push({nd, u1, u2});
                    }
                }
            }
        }
        cout << (best == INF ? -1 : best) << '\n';
    }

    return 0;
}

