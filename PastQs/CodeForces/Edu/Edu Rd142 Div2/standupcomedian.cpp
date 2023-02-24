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

    ll t;
    cin >> t;

    while (t--) {
        vector<ll> a(4);
        FOR (i, 4) {
            cin >> a[i];
        }
        ll phase_1 = a[0], phase_2 = 0, phase_3 = 0;
        if (phase_1 > 0) {
            phase_2 = min(a[1], a[2]) * 2;
            phase_3 = min(a[0] + 1, a[1] + a[2] + a[3] - phase_2);
        } else {
            phase_3 = min(a[0] + 1, a[1] + a[2] + a[3]);
        }
        ll rv = phase_1 + phase_2 + phase_3;
        cout << rv << '\n';
    }


    return 0;
}