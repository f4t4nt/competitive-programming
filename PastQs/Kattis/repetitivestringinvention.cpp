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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str s;
    cin >> s;
    ll n = sz(s);
    vector<ll> match(n + 1);
    vector<vector<ll>> pre(n + 1, vector<ll>(n + 1));
    FORR (i, n) {
        FOB (j, i + 1, n) {
            if (s[i] == s[j]) {
                pre[i][j] = pre[i + 1][j + 1] + 1;
            }
            pre[j][i] = pre[i][j];
        }
    }

    ll rv0 = 0, rv1 = 0;
    FOR (i, n) {
        FOB (j, i, n) {
            ll len = j - i + 1, tmp = 0;
            FOR (k, n) {
                match[k] = (pre[k][i] >= len);
                tmp += match[k];
            }
            ll lo = max(0LL, i - len + 1), hi = j;
            FOB (k, lo, (hi + 1)) {
                tmp -= match[k];
            }
            rv1 += tmp;
            FORR (k, i) {
                lo--, hi++;
                if (lo >= 0) {
                    tmp -= match[lo];
                }
                if (hi < n) {
                    tmp -= match[hi];
                }
                if (pre[k][j + 1] >= i - k) {
                    rv0 += tmp;
                }
            }
        }
    }
    cout << rv0 + rv1 / 2 << '\n';

    return 0;
}