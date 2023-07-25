#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        vector<ll> arms(3), legs(3);
        FOR (i, 3) {
            cin >> arms[i];
            cin >> legs[i];
        }
        ll maxa = max(arms[2] / arms[0], legs[2] / legs[0]) + 1;
        vector<pair<ll, ll>> rv;
        while (maxa > 0) {
            ll rem_arms = arms[2] - maxa * arms[0],
                rem_legs = legs[2] - maxa * legs[0];
            if (rem_arms > 0 && rem_legs > 0 &&
                rem_arms % arms[1] == 0 && rem_legs % legs[1] == 0 &&
                rem_arms / arms[1] == rem_legs / legs[1]
            ) {
                rv.pb({maxa, rem_arms / arms[1]});
                if (sz(rv) == 2) {
                    break;
                }
            }
            maxa--;
        }
        if (sz(rv) != 1) {
            cout << "?\n";
        } else {
            cout << rv[0].first << ' ' << rv[0].second << '\n';
        }
    }

    return 0;
}