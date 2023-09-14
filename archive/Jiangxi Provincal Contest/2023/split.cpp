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

    ll n, q;
    cin >> n;
    vector<ll> a(n), rv(n);
    FOR (i, n) {
        cin >> a[i];
    }
    multiset<ll> diff;
    FOB (i, 1, n) {
        diff.insert(abs(a[i] - a[i - 1]));
    }
    ll i = 0;
    FOB (it, diff.begin(), diff.end()) {
        i++;
        rv[i] = rv[i - 1] + *it;
    }
    cin >> q;
    while (q--) {
        ll t;
        cin >> t;
        if (t == 0) {
            ll x;
            cin >> x;
        } else {
            ll k;
            cin >> k;
            cout << rv[n - k] << '\n';
        }
    }

    return 0;
}