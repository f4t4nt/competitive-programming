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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, t;
    cin >> n >> t;
    vector<ll> read(n), code(n);
    vector<ld> prob(n);
    FOR (i, n) {
        cin >> read[i] >> code[i] >> prob[i];
    }
    vector<vector<ld>> solve(t + 1, vector<ld>(n)), cur(t + 1, vector<ld>(1 << n));
    cur[0][0] = 1;
    FOR (ct, t + 1) {
        if (ct > 0) {
            FOR (i, n) {
                solve[ct][i] += solve[ct - 1][i];
            }
        }
        FOR (i, 1 << n) {
            if (cur[ct][i] == 0) {
                continue;
            }
            ld unread = 0, denom = 0;
            FOR (j, n) {
                if ((i & (1 << j)) == 0) {
                    unread++;
                    denom += solve[ct][j];
                }
            }
            FOR (j, n) {
                if ((i & (1 << j)) == 0) {
                    ld readp = (denom == 0 ? 1 / unread : solve[ct][j] / denom);
                    ll nt = ct + read[j];
                    if (nt <= t) {
                        ld p = cur[ct][i] * readp * (1 - prob[j]);
                        cur[nt][i | (1 << j)] += p;
                    }
                    nt += code[j];
                    if (nt <= t) {
                        ld p = cur[ct][i] * readp * prob[j];
                        cur[nt][i | (1 << j)] += p;
                        solve[nt][j] += p;
                    }
                }
            }
        }
    }
    FOR (i, n) {
        cout << fixed << setprecision(10) << solve[t][i] << '\n';
    }

    return 0;
}