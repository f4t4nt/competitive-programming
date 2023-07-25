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

    ll T;
    cin >> T;
    FOR (t, T) {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n), c(n);
        FOR (i, n) {
            cin >> a[i] >> b[i] >> c[i];
        }
        ll rv = 0;
        vector<ll> h(1e4 + 2), v(1e4 + 2);
        FOR (x, 1e4 + 1) {
            h.assign(1e4 + 2, 0);
            v.assign(1e4 + 2, 0);
            FOR (i, n) {
                if (c[i] <= x && a[i] + b[i] + x <= 1e4) {
                    v[a[i]]++;
                    h[b[i]]++;
                }
            }
            ll q = 0;
            FOR (y, 1e4 - x + 1) {
                q += v[y] - h[1e4 - x - y + 1];
                rv = max(rv, q);
            }
        }
        cout << "Case #" << t + 1 << ": " << rv << '\n';
    }

    return 0;
}