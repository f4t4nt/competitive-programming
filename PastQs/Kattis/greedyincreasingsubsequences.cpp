#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (int) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(int x = 0; x < (int) e; x++)
#define FORR(x, e) for(int x = (int) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(int x = 0; x < (int) e; x += (int) i)
#define FOBI(x, b, e, i) for(int x = (int) b; x < (int) e; x += (int) i)
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

    ll n;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
    }
    vector<vector<ll>> rv;
    rv.pb({a[0]});
    FOB (i, 1, n) {
        ll lo = 0, hi = sz(rv);
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (rv[mid].back() < a[i]) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        if (lo == sz(rv)) {
            rv.pb({a[i]});
        } else {
            rv[lo].pb(a[i]);
        }
    }

    cout << sz(rv) << '\n';
    FORE (x, rv) {
        FORE (y, x) {
            cout << y << ' ';
        }
        cout << '\n';
    }

    return 0;
}