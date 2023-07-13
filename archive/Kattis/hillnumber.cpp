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

bool is_hill(vector<ll> &n) {
    bool dec = false;
    FOR (i, sz(n) - 1) {
        if (dec && n[i] < n[i + 1]) {
            return false;
        }
        if (n[i] > n[i + 1]) {
            dec = true;
        }
    }
    return true;
}

ll solve(
    ll k,
    ll last,
    bool up,
    bool eq,
    vector<ll> &n,
    vector<vector<vector<vector<ll>>>> &dp
) {
    if (k == sz(n)) {
        return 1;
    }
    if (dp[k][last][up][eq] != -1) {
        return dp[k][last][up][eq];
    }
    ll rv = 0;
    if (up) {
        FOB (i, last + 1, 10) {
            if (eq && i > n[k]) {
                break;
            }
            if (!eq || i < n[k]) {
                rv += solve(k + 1, i, up, false, n, dp);
            } else {
                rv += solve(k + 1, i, up, true, n, dp);
            }
        }
    }
    FOR (i, last + 1) {
        if (eq && i > n[k]) {
            break;
        }
        bool nup = up && i == last;
        if (!eq || i < n[k]) {
            rv += solve(k + 1, i, nup, false, n, dp);
        } else {
            rv += solve(k + 1, i, nup, true, n, dp);
        }
    }
    return dp[k][last][up][eq] = rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    str s;
    cin >> s;
    vector<ll> n;
    FORE (x, s) {
        n.pb(x - '0');
    }
    if (!is_hill(n)) {
        cout << -1 << '\n';
        return 0;
    }
    vector<vector<vector<vector<ll>>>> dp(sz(n),
        vector<vector<vector<ll>>>(10,
        vector<vector<ll>>(2,
        vector<ll>(2, -1))));
    ll rv = solve(0, 0, true, true, n, dp) - 1;
    cout << rv << '\n';

    return 0;
}