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

bool solve(ll depth, vector<ll> &answer_key, vector<vector<ll>> &adj) {
    FOR (i, sz(answer_key)) {
        if (answer_key[i] > 0) {
            FORE (u, adj[2 * i]) {
                if (u % 2 == 0) {
                    if (answer_key[u / 2] < 0) {
                        return false;
                    } elif (answer_key[u / 2] == 0) {
                        answer_key[u / 2] = depth;
                    }
                } else {
                    if (answer_key[u / 2] > 0) {
                        return false;
                    } elif (answer_key[u / 2] == 0) {
                        answer_key[u / 2] = -depth;
                    }
                }
            }
        } elif (answer_key[i] < 0) {
            FORE (u, adj[2 * i + 1]) {
                if (u % 2 == 0) {
                    if (answer_key[u / 2] < 0) {
                        return false;
                    } elif (answer_key[u / 2] == 0) {
                        answer_key[u / 2] = depth;
                    }
                } else {
                    if (answer_key[u / 2] > 0) {
                        return false;
                    } elif (answer_key[u / 2] == 0) {
                        answer_key[u / 2] = -depth;
                    }
                }
            }
        }
    }
    FOR (i, sz(answer_key)) {
        if (answer_key[i] == 0) {
            answer_key[i] = -depth - 1;
            if (!solve(depth + 1, answer_key, adj)) {
                FOR (j, sz(answer_key)) {
                    if (abs(answer_key[j]) > depth) {
                        answer_key[j] = 0;
                    }
                }
                answer_key[i] = depth + 1;
                if (!solve(depth + 1, answer_key, adj)) {
                    FOR (j, sz(answer_key)) {
                        if (abs(answer_key[j]) > depth) {
                            answer_key[j] = 0;
                        }
                    }
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    ll n, k;
    cin >> n >> k;
    vector<str> answers(n);
    vector<pair<ll, ll>> edges;
    FOR (i, n) {
        cin >> answers[i];
        vector<ll> tmp(k);
        FOR (j, k) {
            if (answers[i][j] == 'T') {
                tmp[j] = 1;
            } elif (answers[i][j] == 'F') {
                tmp[j] = -1;
            }
        }
        FOR (j, k) {
            if (tmp[j] == 0) {
                continue;
            }
            FOR (l, k) {
                if (j == l || tmp[l] == 0) {
                    continue;
                }
                ll q1 = tmp[j] == 1 ? 2 * j : 2 * j + 1;
                ll q2 = tmp[l] == 1 ? 2 * l + 1 : 2 * l;
                edges.pb(mp(q1, q2));
            }
        }
    }
    // find SCCs
    vector<vector<ll>> adj(k * 2), adj_rev(k * 2);
    FORE (edge, edges) {
        ll a, b;
        tie(a, b) = edge;
        adj[a].pb(b);
        adj_rev[b].pb(a);
    }
    vector<ll> scc(k * 2, -1);
    vector<ll> scc_stack;
    vector<bool> visited(k * 2, false);
    function<void(ll)> dfs = [&](ll v) {
        visited[v] = true;
        FORE (u, adj[v]) {
            if (!visited[u]) {
                dfs(u);
            }
        }
        scc_stack.pb(v);
    };
    FOR (i, k * 2) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    ll scc_count = 0;
    flip(scc_stack);
    visited.assign(k * 2, false);
    function<void(ll)> dfs_rev = [&](ll v) {
        visited[v] = true;
        scc[v] = scc_count;
        FORE (u, adj_rev[v]) {
            if (!visited[u]) {
                dfs_rev(u);
            }
        }
    };
    FORE (v, scc_stack) {
        if (!visited[v]) {
            dfs_rev(v);
            scc_count++;
        }
    }
    // check if there is a contradiction
    FOR (i, k) {
        if (scc[2 * i] == scc[2 * i + 1]) {
            cout << -1 << '\n';
            return 0;
        }
    }
    vector<ll> answer_key(k, 0);
    ll i = 0;
    while (i <= k) {
        answer_key.assign(k, 0);
        FOR (j, min(i, k)) {
            answer_key[j] = 1;
        }
        if (i < k) {
            answer_key[i] = -1;
        }
        if (solve(1, answer_key, adj)) {
            break;
        } else {
            i++;
        }
    }
    str rv;
    FOR (i, k) {
        rv += answer_key[i] > 0 ? 'T' : 'F';
    }
    cout << rv << '\n';
    return 0;
}