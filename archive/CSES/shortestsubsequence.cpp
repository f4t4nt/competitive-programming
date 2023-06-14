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

    str s, rv;
    cin >> s;

    ll count = 0;
    vector<bool> appeared(4);

    FOR (i, sz(s)) {
        ll c;
        if (s[i] == 'A') c = 0;
        elif (s[i] == 'C') c = 1;
        elif (s[i] == 'G') c = 2;
        else c = 3;

        if (!appeared[c]) {
            appeared[c] = true;
            count++;
            if (count == 4) {
                rv += s[i];
                count = 0;
                appeared = vector<bool>(4);
            }
        }
    }

    FOR (i, 4) {
        if (!appeared[i]) {
            rv += "ACGT"[i];
            break;
        }
    }

    cout << rv << '\n';

    return 0;
}