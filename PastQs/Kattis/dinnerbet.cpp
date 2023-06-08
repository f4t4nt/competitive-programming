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

vector<vector<ld>> nCk(60, vector<ld>(60, 0));

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOR (i, 60) {
        nCk[i][0] = 1;
        nCk[i][i] = 1;
    }
    FOB (i, 1, 60) FOB (j, 1, i) {
        nCk[i][j] = nCk[i - 1][j] + nCk[i - 1][j - 1];
    }

    ll n, d, cnt, tmp;
    cin >> n >> d >> cnt;
    set<ll> cesar, raul;
    vector<ll> cnts = {0, 0, 0};
    FOR (i, cnt) {
        cin >> tmp;
        cesar.insert(tmp);
    }
    FOR (i, cnt) {
        cin >> tmp;
        raul.insert(tmp);
        if (cesar.count(tmp)) {
            cnts[0]++;
        } else {
            cnts[2]++;
        }
    }
    FORE (i, cesar) {
        if (!raul.count(i)) {
            cnts[1]++;
        }
    }
    vector<vector<vector<ld>>> dp(cnts[0] + 1,
        vector<vector<ld>>(cnts[1] + 1,
        vector<ld>(cnts[2] + 1)));
    FOR (a, cnts[0] + 1) FOR (b, cnts[1] + 1) FOR (c, cnts[2] + 1) {
        if (a == 0 && (b == 0 || c == 0)) continue;
        ld tmp = 1;
        FOR (i, cnts[0] + 1) FOR (j, cnts[1] + 1) FOR (k, cnts[2] + 1) {
            if (i + j + k == 0) continue;
            if (i + j + k > d) continue;
            if (i > a || j > b || k > c) continue;
            tmp += dp[a - i][b - j][c - k] *
                nCk[a][i] * nCk[b][j] * nCk[c][k] *
                nCk[n - a - b - c][d - i - j - k] /
                nCk[n][d];
        }
        dp[a][b][c] = tmp / (1 - nCk[n - a - b - c][d] / nCk[n][d]);
    }
    cout << fixed << setprecision(10) << dp[cnts[0]][cnts[1]][cnts[2]] << '\n';

    return 0;
}