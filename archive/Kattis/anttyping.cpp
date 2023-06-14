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

ll bruteforce(str &s) {
    vector<vector<ll>> counts(9, vector<ll>(9));
    FOB (i, 1, sz(s)) {
        counts[s[i - 1] - '1'][s[i] - '1']++;
    }

    vector<ll> keyboard(9);
    iota(keyboard.begin(), keyboard.end(), 0);

    ll rv = 1e18;
    do {
        ll cv = 0;
        vector<vector<ll>> dist(9, vector<ll>(9));
        while (keyboard[cv] != s[0] - '1') {
            cv++;
        }
        FOR (len, 9) {
            ll i = 0, j = len;
            while (j < 9) {
                dist[keyboard[i]][keyboard[j]] = len;
                dist[keyboard[j]][keyboard[i]] = len;
                i++;
                j++;
            }
        }
        FOR (i, 9) {
            FOR (j, 9) {
                cv += dist[i][j] * counts[i][j];
            }
        }
        rv = min(rv, cv);
    } while (next_permutation(keyboard.begin(), keyboard.end()));

    return rv + sz(s);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str s;
    cin >> s;
    cout << bruteforce(s) << '\n';

    return 0;
}