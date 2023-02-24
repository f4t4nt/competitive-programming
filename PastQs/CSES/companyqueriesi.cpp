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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> parent(n, vector<ll>(30));
    // ll t[200000], parent[200000][30];
    parent[0][0] = -1;
    FOB (i, 1, n) {
        cin >> parent[i][0];
        parent[i][0]--;
    }
    FOR (i, 29) {
        FOR (j, n) {
            if (parent[j][i] == -1) {
                parent[j][i + 1] = -1;
            } else {
                parent[j][i + 1] = parent[parent[j][i]][i];
            }
        }
    }

    while (q--) {
        ll x, k;
        cin >> x >> k;
        x--;
        bool valid = true;
        FOR (i, 30) {
            if (k & (1 << i)) {
                x = parent[x][i];
                if (x == -1) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) {
            cout << x + 1 << '\n';
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}