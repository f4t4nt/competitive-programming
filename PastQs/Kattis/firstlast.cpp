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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

map<tuple<ll, ll, vector<vector<ll>>>, bool> memo;

// [i, j] incoming, [j, k] outgoing
bool dfs(ll i, ll j, vector<vector<ll>> &adj, bool alice = false) {
    if (memo.find({i, j, adj}) != memo.end()) {
        return memo[{i, j, adj}];
    }
    FOR (k, sz(adj)) {
        if (adj[j][k] > 0) {
            adj[j][k]--;
            if (!dfs(i, k, adj, !alice)) {
                adj[j][k]++;
                memo[{i, j, adj}] = true;
                return true;
            }
            adj[j][k]++;
        }
    }
    memo[{i, j, adj}] = false;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n;
    cin >> n;
    vector<str> w(n);
    map<ch, ll> ref;
    FOR (i, n) {
        cin >> w[i];
        if (ref.find(w[i][0]) == ref.end()) {
            ref[w[i][0]] = sz(ref);
        }
        if (ref.find(w[i].back()) == ref.end()) {
            ref[w[i].back()] = sz(ref);
        }
    }
    vector<vector<ll>> cnts(sz(ref), vector<ll>(sz(ref))), adj = cnts;
    FOR (i, n) {
        cnts[ref[w[i][0]]][ref[w[i].back()]]++;
    }
    FOR (i, sz(ref)) {
        adj[i][i] = (cnts[i][i] + 1) % 2 + 1;
    }
    FOR (i, sz(ref)) {
        FOB (j, i + 1, sz(ref)) {
            ll tmp = min(cnts[i][j], cnts[j][i]) - 1;
            adj[i][j] = cnts[i][j] - tmp;
            adj[j][i] = cnts[j][i] - tmp;
        }
    }
    ll rv = 0;
    vector<vector<bool>> adds(sz(ref), vector<bool>(sz(ref)));
    FOR (i, sz(ref)) {
        bool add = false;
        FOR (j, sz(ref)) {
            auto adj0 = adj;
            adj0[i][j]--;
            if (!dfs(i, j, adj0)) {
                rv += cnts[i][j];
            }
        }
    }
    cout << rv << '\n';

    return 0;
}