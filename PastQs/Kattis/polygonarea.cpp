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

ld shoelace(vector<pair<ld, ld>> &v) {
    ld area = 0;
    FOR (i, sz(v)) {
        area += (v[i].first * v[(i + 1) % sz(v)].second) -
            (v[i].second * v[(i + 1) % sz(v)].first);
    }
    return area / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<pair<ld, ld>> v(n);
        FORE (p, v) {
            cin >> p.first >> p.second;
        }
        ld rv = shoelace(v);
        if (rv < 0) {
            cout << "CW ";
            rv *= -1;
        } else {
            cout << "CCW ";
        }
        cout << fixed << setprecision(1) << rv << '\n';
    }

    return 0;
}