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
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll L, H, k;
    cin >> L >> H >> k;
    vector<vector<ch>> grid(H, vector<ch>(L, '_'));
    ch c = 'a';
    FOR (i, k) {
        ll l, h, a, b;
        cin >> l >> h >> a >> b;
        FOB (x, b, min(b + h, H)) {
            FOB (y, a, min(a + l, L)) {
                grid[x][y] = c;
            }
        }
        c++;
    }
    FOR (i, H) {
        FOR (j, L) {
            cout << grid[i][j];
        }
        cout << '\n';
    }

    return 0;
}