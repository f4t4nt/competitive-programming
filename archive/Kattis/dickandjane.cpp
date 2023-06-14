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
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

    ll s, p, y, j;

    while (cin >> s >> p >> y >> j) {
        ld spot_ld = ((ld) j + s + y + 12) / 3,
            puff_ld = ((ld) j - 2 * s + y + 12) / 3,
            yertle_ld = ((ld) j + s - 2 * y + 12) / 3;
        ll spot = spot_ld, puff = puff_ld, yertle = yertle_ld;
        if (spot + puff + yertle != 12 + j) {
            spot++;
        }
        if (spot + puff + yertle == 10 + j) {
            puff++;
            yertle++;
        } elif (spot + puff + yertle == 11 + j) {
            if (spot - puff > s + 1) {
                puff++;
            } elif (spot - yertle > y + 1 || puff - yertle >= p + 1) {
                yertle++;
            } else {
                puff++;
            }
        } elif (spot + puff + yertle != 12 + j) {
            assert(false);
        }
        // cout << spot_ld << ' ' << puff_ld << ' ' << yertle_ld << '\n';
        cout << spot << ' ' << puff << ' ' << yertle << '\n';
    }

    return 0;
}