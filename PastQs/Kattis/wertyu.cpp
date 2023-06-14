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

vector<str> keyboard = {
    "`1234567890-=",
    "QWERTYUIOP[]\\",
    "ASDFGHJKL;'",
    "ZXCVBNM,./"
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    map<ch, ch> ref;
    FORE (row, keyboard) {
        FOB (i, 1, sz(row)) {
            ref[row[i]] = row[i - 1];
        }
    }
    str line;
    while (getline(cin, line)) {
        FORE (ch, line) {
            if (ch == ' ') {
                cout << ' ';
            } else {
                cout << ref[ch];
            }
        }
        cout << '\n';
    }

    return 0;
}