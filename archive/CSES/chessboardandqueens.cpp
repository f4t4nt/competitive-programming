#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

ll dfs(ll q, vector<str> grid, vector<set<ll>> bans) {
    if (q == 8) {
        return 1;
    }
    ll rv = 0;
    FOR (i, 8) {
        FOR (j, 8) {
            if (grid[i][j] != '.') {
                continue;
            }
            if (bans[0].count(i) || bans[1].count(j) || bans[2].count(i + j) || bans[3].count(i - j)) {
                continue;
            }
            vector<set<ll>> new_bans = bans;
            new_bans[0].insert(i);
            new_bans[1].insert(j);
            new_bans[2].insert(i + j);
            new_bans[3].insert(i - j);
            grid[i][j] = 'Q';
            rv += dfs(q + 1, grid, new_bans);
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<str> grid(8);
    FOR (i, 8) {
        cin >> grid[i];
    }
    // x, y, x+y, x-y
    vector<set<ll>> bans(4);
    ll rv = dfs(0, grid, bans);
    cout << rv << '\n';

    return 0;
}