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

constexpr ll MOD = 12345647;

ll solve(ll i, ll big, ll carry, str &n, str &l, vector<vector<vector<ll>>> &dp) {
    if (i == sz(n)) {
        return carry == 0;
    }
    if (dp[i][big][carry] != -1) {
        return dp[i][big][carry];
    }
    ll rv = 0;
    FOB (d1, ((big & 1) ? 0 : l[i] - '0'), 10) {
        if (d1 == 3) {
            continue;
        }
        FOB (d2, ((big & 2) ? 0 : l[i] - '0'), 10) {
            if (d2 == 3) {
                continue;
            }
            FOB (d3, ((big & 4) ? 0 : l[i] - '0'), 10) {
                if (d3 == 3) {
                    continue;
                }
                ll big2 = big;
                if (d1 > l[i] - '0') {
                    big2 |= 1;
                }
                if (d2 > l[i] - '0') {
                    big2 |= 2;
                }
                if (d3 > l[i] - '0') {
                    big2 |= 4;
                }
                ll carry2 = carry * 10 + n[i] - '0' - d1 - d2 - d3;
                if (0 <= carry2 && carry2 <= 2) {
                    rv += solve(i + 1, big2, carry2, n, l, dp);
                    rv %= MOD;
                }
            }
        }
    }
    return dp[i][big][carry] = rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        str n, l;
        cin >> n >> l;
        while (sz(l) < sz(n)) {
            l = '0' + l;
        }
        vector<vector<vector<ll>>> dp(sz(n) + 1,
            vector<vector<ll>>(8,
                vector<ll>(3, -1)));
        ll rv = solve(0, 0, 0, n, l, dp);
        cout << rv << '\n';
    }

    return 0;
}