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

    str line;
    while (true) {
        getline(cin, line);
        ll x = stoll(line);
        if (x == 0) break;
        getline(cin, line);
        transform(all(line), line.begin(), ::toupper);
        line.erase(remove(all(line), ' '), line.end());
        vector<str> ref(x);
        ll len = sz(line) / x,
            xtra = sz(line) % x;
        FOR (i, x) {
            if (i < xtra) {
                ref[i] = line.substr(i * (len + 1), len + 1);
            } else {
                ref[i] = line.substr(xtra * (len + 1) + (i - xtra) * len, len);
            }
        }
        str rv = "";
        FOR (j, len + 1) {
            FOR (i, x) {
                if (j >= sz(ref[i])) {
                    break;
                }
                rv += ref[i][j];
            }
        }
        cout << rv << '\n';
    }

    return 0;
}