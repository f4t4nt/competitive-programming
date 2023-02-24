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

    ll n, rv = 1;
    cin >> n;
    vector<ll> x(n);
    FOR (i, n) {
        cin >> x[i];
    }
    FOB (i, 1, n - 1) {
        ll len = 1, lo = i - 1, hi = i + 1, prev = x[i];
        while (lo >= 0 && hi < n && x[lo] == x[hi] && x[lo] < prev) {
            len += 2;
            prev = x[lo];
            lo--;
            hi++;
        }
        rv = max(rv, len);
    }
    if (rv == 1) {
        cout << -1 << '\n';
    } else {
        cout << rv << '\n';
    }

    return 0;
}