#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define sz(C) (ll) C.size()
#define pb push_back

// -----------------------------------------------------------------------------
//  2-SAT
// -----------------------------------------------------------------------------
//  Supports:   - either(f, j)      f or j holds        ts.either(0, ~3)
//              - set_value(x)      x holds             ts.set_value(~2)
//              - at_most_one(li)   <= 1 of li holds    ts.at_most_one({0, ~1, 2})
//              - solve()           true iff satisfiable; fills values[]
//  Notes:      - variables are 0..n-1; ~x anywhere a literal goes means
//                "x false"
//              - at_most_one adds sz(li) - 2 helper variables
//              - literal x lives at node 2x, ~x at 2x + 1
//              - recursive Tarjan on the implication graph, depth can reach 2n
//  Complexity: O(n + clauses)
// -----------------------------------------------------------------------------
struct TwoSat {
    ll n;                    // variable count, grows in at_most_one
    vector<vector<ll>> gr;   // implication graph over 2n literals
    vector<ll> values;       // 0 / 1 per variable, valid after a true solve()
    vector<ll> val, comp, z; // tarjan state
    ll timer = 0;

    TwoSat(ll n) : n(n), gr(2 * n) {}

    // clauses
    ll add_var() {
        gr.pb({}), gr.pb({});
        return n++;
    }

    // f or j holds
    void either(ll f, ll j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].pb(j ^ 1);
        gr[j].pb(f ^ 1);
    }

    // x holds
    void set_value(ll x) { either(x, x); }

    // at most one of li holds
    void at_most_one(const vector<ll> &li) {
        if (sz(li) < 2) return;
        ll cur = ~li[0];
        for (ll i = 2; i < sz(li); i++) {
            ll nxt = add_var();
            either(cur, ~li[i]);
            either(cur, nxt);
            either(~li[i], nxt);
            cur = ~nxt;
        }
        either(cur, ~li[1]);
    }

    // solving
    ll dfs(ll i) {
        ll low = val[i] = ++timer, x;
        z.pb(i);
        for (ll j : gr[i]) if (!comp[j]) low = min(low, val[j] ? val[j] : dfs(j));
        if (low == val[i]) do {
            x = z.back();
            z.pop_back();
            comp[x] = low;
            if (values[x >> 1] == -1) values[x >> 1] = x & 1;
        } while (x != i);
        return val[i] = low;
    }

    bool solve() {
        values.assign(n, -1);
        val.assign(2 * n, 0);
        comp = val;
        for (ll i = 0; i < 2 * n; i++) if (!comp[i]) dfs(i);
        for (ll i = 0; i < n; i++) if (comp[2 * i] == comp[2 * i + 1]) return false;
        return true;
    }
};
