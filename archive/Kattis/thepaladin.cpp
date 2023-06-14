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
    vector<vector<ll>> costs(26, vector<ll>(26)), dist0(26, vector<ll>(26, 1e9));
    FOR (i, n) {
        ch a, b;
        ll c;
        cin >> a >> b >> c;
        costs[a - 'a'][b - 'a'] = c;
    }
    FOR (i, 26) {
        FOR (j, i + 1) {
            if (costs[i][j] == 0 || costs[j][i] == 0) {
                costs[i][j] = costs[j][i] = 1e9;
            } else {
                costs[i][j] += costs[j][i];
                costs[j][i] = costs[i][j];
            }
        }
    }

    if (k % 2 == 0) {
        FOR (i, 26) {
            if (costs[i][i] != 1e9) {
                dist0[i][i] = costs[i][i] / 2;
            } else {
                dist0[i][i] = 1e9;
            }
        }
    } else {
        dist0 = costs;
    }
    k = k / 2 - 1;

    while (k--) {
        vector<vector<ll>> dist1(26, vector<ll>(26, 1e9));
        FOR (i, 26) {
            FOR (j, 26) {
                FOR (l, 26) {
                    dist1[i][j] = min(dist1[i][j], dist0[i][l] + costs[l][j]);
                }
            }
        }
        dist0 = dist1;
    }

    ll rv = 1e9;
    FOR (i, 26) {
        FOR (j, 26) {
            rv = min(rv, dist0[i][j]);
        }
    }
    if (rv == 1e9) {
        cout << -1 << '\n';
    } else {
        cout << rv << '\n';
    }

    return 0;
}