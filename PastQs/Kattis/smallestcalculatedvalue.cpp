#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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

    ll a, b, c, rv = 1e18;
    cin >> a >> b >> c;

    FOR (i, 4) {
        ll ab = 1e18;
        if (i == 0) {
            ab = a + b;
        } elif (i == 1) {
            ab = a - b;
        } elif (i == 2) {
            ab = a * b;
        } elif (i == 3 && a % b == 0) {
            ab = a / b;
        }
        FOR (j, 4) {
            ll abc = 1e18;
            if (j == 0) {
                abc = ab + c;
            } elif (j == 1) {
                abc = ab - c;
            } elif (j == 2) {
                abc = ab * c;
            } elif (j == 3 && ab % c == 0) {
                abc = ab / c;
            }
            if (abc >= 0) {
                rv = min(abc, rv);
            }
        }
    }

    cout << rv << '\n';

    return 0;
}