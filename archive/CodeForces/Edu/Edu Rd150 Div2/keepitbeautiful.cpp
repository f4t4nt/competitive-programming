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

    ll t;
    cin >> t;
    while (t--) {
        ll q;
        cin >> q;
        bool dec = false;
        ll x0 = -1, xp = -1, x = -1;
        FOR (i, q) {
            cin >> x;
            if (x0 == -1) {
                x0 = x;
            }
            if (!dec) {
                if (x < xp && x <= x0) {
                    dec = true;
                    cout << 1;
                    xp = x;
                } elif (x >= xp) {
                    cout << 1;
                    xp = x;
                } else {
                    cout << 0;
                }
            } else {
                if (x >= xp && x <= x0) {
                    cout << 1;
                    xp = x;
                } else {
                    cout << 0;
                }
            }
        }
        cout << '\n';
    }

    return 0;
}