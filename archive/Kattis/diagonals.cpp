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

bool valid(ll &n, vector<vector<ll>> &ref, vector<vector<ch>> &rv) {
    vector<vector<ll>> min_ref(n + 1, vector<ll>(n + 1, 0)), max_ref(n + 1, vector<ll>(n + 1, 4));
    max_ref[0][0] = 1, max_ref[0][n] = 1, max_ref[n][0] = 1, max_ref[n][n] = 1;
    FOB (i, 1, n) {
        max_ref[0][i] = 2, max_ref[n][i] = 2, max_ref[i][0] = 2, max_ref[i][n] = 2;
    }
    vector<vector<ll>> adj((n + 1) * (n + 1));
    FOR (i, n) {
        FOR (j, n) {
            if (rv[i][j] == '\\') {
                min_ref[i][j]++;
                min_ref[i + 1][j + 1]++;
                max_ref[i + 1][j]--;
                max_ref[i][j + 1]--;
                adj[i * (n + 1) + j].pb((i + 1) * (n + 1) + j + 1);
                adj[(i + 1) * (n + 1) + j + 1].pb(i * (n + 1) + j);
            } elif (rv[i][j] == '/') {
                min_ref[i + 1][j]++;
                min_ref[i][j + 1]++;
                max_ref[i][j]--;
                max_ref[i + 1][j + 1]--;
                adj[(i + 1) * (n + 1) + j].pb(i * (n + 1) + j + 1);
                adj[i * (n + 1) + j + 1].pb((i + 1) * (n + 1) + j);
            }
        }
    }
    FOR (i, n + 1) {
        FOR (j, n + 1) {
            if (ref[i][j] != -1 && (min_ref[i][j] > ref[i][j] || max_ref[i][j] < ref[i][j])) {
                return false;
            }
        }
    }
    vector<bool> visited((n + 1) * (n + 1), false);
    vector<ll> parent((n + 1) * (n + 1), -1);
    function<bool(ll)> dfs = [&](ll u) {
        visited[u] = true;
        FORE (v, adj[u]) {
            if (!visited[v]) {
                parent[v] = u;
                if (dfs(v)) {
                    return true;
                }
            } elif (parent[u] != v) {
                return true;
            }
        }
        return false;
    };
    FOR (i, n + 1) {
        FOR (j, n + 1) {
            if (!visited[i * (n + 1) + j] && dfs(i * (n + 1) + j)) {
                return false;
            }
        }
    }
    return true;
}

vector<vector<ch>> solve(ll &n, vector<vector<ll>> &ref, vector<vector<ch>> rv) {
    if (!valid(n, ref, rv)) {
        return vector<vector<ch>>();
    }
    vector<vector<ll>> min_ref(n + 1, vector<ll>(n + 1, 0)), max_ref(n + 1, vector<ll>(n + 1, 4));
    max_ref[0][0] = 1, max_ref[0][n] = 1, max_ref[n][0] = 1, max_ref[n][n] = 1;
    FOB (i, 1, n) {
        max_ref[0][i] = 2, max_ref[n][i] = 2, max_ref[i][0] = 2, max_ref[i][n] = 2;
    }
    FOR (i, n) {
        FOR (j, n) {
            if (rv[i][j] == '\\') {
                min_ref[i][j]++;
                min_ref[i + 1][j + 1]++;
                max_ref[i + 1][j]--;
                max_ref[i][j + 1]--;
            } elif (rv[i][j] == '/') {
                min_ref[i + 1][j]++;
                min_ref[i][j + 1]++;
                max_ref[i][j]--;
                max_ref[i + 1][j + 1]--;
            }
        }
    }
    bool change = false;
    FOR (i, n + 1) {
        FOR (j, n + 1) {
            if (ref[i][j] != -1 && min_ref[i][j] != max_ref[i][j]) {
                if (ref[i][j] == max_ref[i][j]) {
                    if (i > 0 && j > 0 && rv[i - 1][j - 1] == ' ') {
                        rv[i - 1][j - 1] = '\\';
                        change = true;
                    }
                    if (i > 0 && j < n && rv[i - 1][j] == ' ') {
                        rv[i - 1][j] = '/';
                        change = true;
                    }
                    if (i < n && j > 0 && rv[i][j - 1] == ' ') {
                        rv[i][j - 1] = '/';
                        change = true;
                    }
                    if (i < n && j < n && rv[i][j] == ' ') {
                        rv[i][j] = '\\';
                        change = true;
                    }
                } elif (ref[i][j] == min_ref[i][j]) {
                    if (i > 0 && j > 0 && rv[i - 1][j - 1] == ' ') {
                        rv[i - 1][j - 1] = '/';
                        change = true;
                    }
                    if (i > 0 && j < n && rv[i - 1][j] == ' ') {
                        rv[i - 1][j] = '\\';
                        change = true;
                    }
                    if (i < n && j > 0 && rv[i][j - 1] == ' ') {
                        rv[i][j - 1] = '\\';
                        change = true;
                    }
                    if (i < n && j < n && rv[i][j] == ' ') {
                        rv[i][j] = '/';
                        change = true;
                    }
                }
            }
        }
    }
    bool filled = true;
    FOR (i, n) {
        FOR (j, n) {
            if (rv[i][j] == ' ') {
                filled = false;
            }
        }
    }
    if (filled && valid(n, ref, rv)) {
        return rv;
    }
    if (change) {
        return solve(n, ref, rv);
    } else {
        FOR (i, n) {
            FOR (j, n) {
                if (rv[i][j] == ' ') {
                    rv[i][j] = '\\';
                    auto rv1 = solve(n, ref, rv);
                    if (!rv1.empty()) {
                        return rv1;
                    }
                    rv[i][j] = '/';
                    auto rv2 = solve(n, ref, rv);
                    if (!rv2.empty()) {
                        return rv2;
                    }
                    return vector<vector<ch>>();
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<vector<ll>> ref(n + 1, vector<ll>(n + 1));
    FOR (i, n + 1) {
        FOR (j, n + 1) {
            ch c;
            cin >> c;
            if (c == '+') {
                ref[i][j] = -1;
            } else {
                ref[i][j] = c - '0';
            }
        }
    }
    vector<vector<ch>> rv(n, vector<ch>(n, ' '));
    // FOR (i, n) {
    //     FOR (j, n) {
    //         cin >> rv[i][j];
    //     }
    // }
    // if (!valid(n, ref, rv)) {
    //     cout << "invalid";
    //     return 0;
    // }
    rv = solve(n, ref, rv);
    FOR (i, n) {
        FOR (j, n) {
            cout << rv[i][j];
        }
        cout << '\n';
    }

    return 0;
}