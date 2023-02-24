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
    ll t;
    cin >> t;
    while (t--) {
        str s;
        cin >> s;
        if (s[0] == s[1] || (s[0] == 'b' && s[1] == 'a')) {
            cout << s[0] << ' ' << s[1] << ' ' << s.substr(2) << '\n';
        } else {
            ll idx = -1;
            FOB (i, 2, sz(s)) {
                if (s[i] == 'a') {
                    idx = i;
                    break;
                }
            }
            if (idx == -1) {
                cout << s.substr(0, sz(s) - 2) << ' ' << s[sz(s) - 2] << ' ' << s[sz(s) - 1] << '\n';
            } else {
                cout << s[0] << ' ' << s.substr(1, idx - 1) << ' ' << s.substr(idx) << '\n';
            }
        }
    }
    return 0;
}