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

// imma show YOU how great i am.

map<vector<ld>, tuple<ll, ld, ld>> mem, mem2;

// what i we pick, what value i pick, what is the probability of winning
tuple<ll, ld, ld> bash(vector<ld> v) {
    if (mem.count(v)) return mem[v];
    if (sz(v) == 0) return mem[v] = {-1, 0, 0};
    if (sz(v) == 1) return mem[v] = {0, v[0], v[0]};
    ld best_prob = -1;
    ll best_id = -1;
    FOR (i, sz(v)) { // what i pick
        ld tmp = 0;
        FOR (j, sz(v)) { // what idiot picks
            if (i == j) {
                tmp += v[i];
            } else {
                vector<ld> nv;
                FOR (k, sz(v)) if (k != i && k != j) nv.pb(v[k]);
                auto [id, val, prob] = bash(nv);
                tmp += prob;
            }
        }
        tmp /= sz(v);
        if (tmp > best_prob) {
            best_prob = tmp;
            best_id = i;
        }
    }
    return mem[v] = {best_id, v[best_id], best_prob};
}

tuple<ll, ld, ld> bash2(vector<ld> v) {
    if (mem2.count(v)) return mem2[v];
    if (sz(v) == 0) return mem2[v] = {-1, 0, 0};
    if (sz(v) == 1) return mem2[v] = {0, v[0], v[0]};
    // i always pick last
    ll i = sz(v) - 1;
    ld tmp = 0;
    FOR (j, sz(v)) { // what idiot picks
        if (i == j) {
            tmp += v[i];
        } else {
            vector<ld> nv;
            FOR (k, sz(v)) if (k != i && k != j) nv.pb(v[k]);
            auto [id, val, prob] = bash2(nv);
            tmp += prob;
        }
    }
    tmp /= sz(v);
    tmp *= v[i];
    return mem2[v] = {i, v[i], tmp};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<ld> tmp = {0, 0, 0, 0, 0, 0, 0, 0, 1};
    auto [id, val, prob] = bash(tmp);
    cout << "mem: \n";
    FORE (e, mem) {
        assert((sz(tmp) - sz(e.first)) % 2 == 0);
        cout << "v: ";
        FORE (f, e.first) cout << f << ' ';
        cout << '\n';
        cout << "id: " << get<0>(e.second) << '\n';
        cout << "val: " << get<1>(e.second) << '\n';
        cout << "prob: " << get<2>(e.second) << '\n';
        cout << '\n';
    }
    auto [id2, val2, prob2] = bash2(tmp);
    cout << "mem2: \n";
    FORE (e, mem2) {
        assert((sz(tmp) - sz(e.first)) % 2 == 0);
        cout << "v: ";
        FORE (f, e.first) cout << f << ' ';
        cout << '\n';
        cout << "id: " << get<0>(e.second) << '\n';
        cout << "val: " << get<1>(e.second) << '\n';
        cout << "prob: " << get<2>(e.second) << '\n';
        cout << '\n';
    }
    return 0;

    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> adj(n);
        FOR (i, m) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].pb(b);
        }
        vector<ld> dp(n);
        dp[n - 1] = 1;
        FORR (i, n - 1) {
            vector<ld> tmp;
            FORE (j, adj[i]) {
                tmp.pb(dp[j]);
            }
            ssort(tmp);
            dp[i] = get<2>(bash(tmp));
        }
        cout << fixed << setprecision(12) << dp[0] << '\n';
    }

    return 0;
}