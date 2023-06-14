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

    ll b, d, c, l;
    cin >> b >> d >> c >> l;
    set<tuple<ll, ll, ll>> rv;
    FOR (i, 251) {
        if (i * b > l) break;
        FOR (j, 251) {
            if (i * b + j * d > l) break;
            FOR (k, 251) {
                if (i * b + j * d + k * c > l) break;
                if (i * b + j * d + k * c == l) {
                    rv.insert({i, j, k});
                }
            }
        }
    }
    if (rv.empty()) {
        cout << "impossible\n";
    } else {
        FORE (x, rv) {
            cout << get<0>(x) << ' ' << get<1>(x) << ' ' << get<2>(x) << '\n';
        }
    }

    return 0;
}