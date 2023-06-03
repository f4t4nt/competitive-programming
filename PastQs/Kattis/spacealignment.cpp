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

struct Cnts {
    ll s, t;

    Cnts(str line) {
        s = 0, t = 0;
        FOR (i, sz(line) - 1) {
            if (line[i] == 's') {
                s++;
            } else {
                t++;
            }
        }
    }

    ll total(ll rate) {
        return s + t * rate;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<str> lines(n);
    FORE (line, lines) {
        cin >> line;
    }

    ll depth = 0;
    vector<vector<Cnts>> cnts(1000);
    FORE (line, lines) {
        if (line.back() == '{') {
            cnts[depth].pb(Cnts(line));
            depth++;
        } else {
            depth--;
            cnts[depth].pb(Cnts(line));
        }
    }

    FOB (rate, 1, 1e3) {
        ll unit = 0;
        if (sz(cnts[1])) unit = cnts[1][0].total(rate);
        bool ok = true;
        FOR (d, 1e3) {
            ll exp = unit * d;
            FORE (cnt, cnts[d]) {
                if (exp != cnt.total(rate)) {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
        }
        if (ok) {
            cout << rate << '\n';
            return 0;
        }
    }
    
    cout << -1 << '\n';
    return 0;
}