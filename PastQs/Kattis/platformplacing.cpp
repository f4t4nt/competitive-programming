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

    ll n, min_len, max_len;
    cin >> n >> min_len >> max_len;
    vector<ll> x(n);
    FOR (i, n) {
        cin >> x[i];
    }
    ssort(x);

    if (n == 1) {
        cout << max_len << '\n';
        return 0;
    }

    FOB (i, 1, n) {
        if (x[i] - x[i - 1] < min_len) {
            cout << -1 << '\n';
            return 0;
        }
    }

    FOR (i, n) {
        x[i] *= 2;
    }

    vector<ll> lens(n, min_len);
    lens[0] = min(max_len, x[1] - x[0] - min_len);
    FOB (i, 1, n - 1) {
        lens[i] = min(max_len, min(x[i] - x[i - 1] - lens[i - 1], x[i + 1] - x[i] - lens[i + 1]));
    }
    lens[n - 1] = min(max_len, x[n - 1] - x[n - 2] - lens[n - 2]);

    ll rv = 0;
    FOR (i, n) {
        rv += lens[i];
    }
    cout << rv << '\n';

    return 0;
}