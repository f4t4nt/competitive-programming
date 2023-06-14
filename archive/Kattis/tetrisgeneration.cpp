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

map<ch, ll> char_to_int = {
    {'J', 0},
    {'L', 1},
    {'S', 2},
    {'Z', 3},
    {'I', 4},
    {'O', 5},
    {'T', 6}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;

    while (t--) {
        str s;
        cin >> s;
        bool rv = false;
        FOR (i, 1 << 7) {
            ll count = 0;
            vector<bool> appeared(7, false);
            FOR (j, 7) {
                if (i & (1 << j)) {
                    count++;
                    appeared[j] = true;
                }
            }
            bool valid = true;
            FOR (j, sz(s)) {
                if (!appeared[char_to_int.at(s[j])]) {
                    count++;
                    appeared[char_to_int.at(s[j])] = true;
                } else {
                    valid = false;
                    break;
                }
                if (count == 7) {
                    appeared = vector<bool>(7, false);
                    count = 0;
                }
            }
            if (valid) {
                rv = true;
                break;
            }
        }
        cout << (rv ? '1' : '0') << '\n';
    }

    return 0;
}