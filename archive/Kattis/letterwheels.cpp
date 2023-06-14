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
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

    vector<str> s(3);
    FOR (i, 3) {
        cin >> s[i];
    }
    ll n = sz(s[0]);

    vector<vector<bool>> valid(3, vector<bool>(n, true));
    FOR (i, n) {
        FOR (j, n) {
            if (s[0][i] == s[1][(i + j) % n]) {
                valid[2][j] = false;
            }
            if (s[0][i] == s[2][(i + j) % n]) {
                valid[1][j] = false;
            }
            if (s[1][i] == s[2][(i + j) % n]) {
                valid[0][j] = false;
            }
        }
    }

    ll rv = 1e18;
    FOR (i, n) {
        FOR (j, n) {
            if (valid[0][(j - i + n) % n] && valid[1][j] && valid[2][i]) {
                rv = min(rv, max(i, j));
                rv = min(rv, max(n - i, n - j));
                rv = min(rv, min(i, n - i) + min(j, n - j));
            }
        }
    }

    cout << (rv == 1e18 ? -1 : rv) << '\n';

    return 0;
}