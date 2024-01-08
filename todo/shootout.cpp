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

// https://open.kattis.com/problems/shootout?tab=metadata

ll n;
vector<ld> p;

// [who's standing][who's turn] = probabilities of winning
map<pair<ll, ll>, vector<ld>> mem;
set<pair<ll, ll>> vis;

vector<ld> dfs(ll state, ll cur, ll cur_sz, bool cache = true) {
    assert(state & (1 << cur));
    if (vis.count({state, cur})) {
        if (!mem.count({state, cur})) {
            return vector<ld>(n, 0);
        } else {
            return mem[{state, cur}];
        }
    }
    vis.insert({state, cur});
    if (state == (1 << cur)) {
        vector<ld> rv(n);
        rv[cur] = 1;
        return mem[{state, cur}] = rv;
    }

    vector<vector<ld>> best(1, vector<ld>(n, -1));
    FOR (i, n) {
        if (state & (1 << i) && i != cur) {
            ll new_state = state ^ (1 << i), nxt = (cur + 1) % n;
            while (!(new_state & (1 << nxt))) {
                nxt = (nxt + 1) % n;
            }
            vector<ld> tmp = dfs(new_state, nxt, cur_sz - 1, cache);
            if (tmp[cur] > best[0][cur]) {
                best = vector<vector<ld>>(1, tmp);
            } elif (tmp[cur] == best[0][cur]) {
                best.pb(tmp);
            }
        }
    }
    vector<ld> if_hit(n);
    FORE (tmp, best) {
        FOR (i, n) {
            if_hit[i] += tmp[i];
        }
    }
    FOR (i, n) {
        if_hit[i] /= sz(best);
    }

    ld all_miss = 1;
    FOR (i, n) {
        if (state & (1 << i)) {
            all_miss *= (1 - p[i]);
        }
    }
    vector<ld> if_miss(n);
    ll nxt = (cur + 1) % n;
    while (!(state & (1 << nxt))) {
        nxt = (nxt + 1) % n;
    }
    assert(cur != nxt);
    if_miss = dfs(state ^ (1 << cur), nxt, cur_sz - 1, false);
    if (all_miss > 0) {
        FOR (i, n) {
            if_miss[i] /= all_miss;
        }
    }

    vector<ld> rv(n);
    FOR (i, n) {
        rv[i] = p[cur] * if_hit[i] + (1 - p[cur]) * if_miss[i];
    }
    if (cache) {
        mem[{state, cur}] = rv;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        p.resize(n);
        mem.clear();
        vis.clear();
        FOR (i, n) {
            cin >> p[i];
            p[i] /= 100;
        }
        vector<ld> rv = dfs((1 << n) - 1, 0, n);
        FORE (x, rv) {
            cout << fixed << setprecision(10) << 100 * x << ' ';
        }
        cout << '\n';
    }

    return 0;
}