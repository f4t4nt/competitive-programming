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

ll counts(ll &idx, ll &mid, map<ll, vector<ll>> &pos, vector<ll> &bs) {
    ll rv = 0;
    FORE (b, bs) {
        // counts of b < idx
        ll lo = lower_bound(all(pos[b]), idx) - pos[b].begin(),
        // total counts of b - (counts of b <= idx + mid) = counts of b > idx + mid
            hi = sz(pos[b]) - (lower_bound(all(pos[b]), idx + mid) - pos[b].begin());
        // total counts of b >= idx and <= idx + mid 
        rv += sz(pos[b]) - lo - hi;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n;
    vector<ll> a(n);
    map<ll, vector<ll>> pos;
    FOR (i, n) {
        cin >> a[i];
        pos[a[i]].pb(i);
    }
    cin >> q;
    while (q--) {
        ll idx, m;
        cin >> idx >> m;
        idx--;
        vector<ll> b(m);
        FOR (i, m) {
            cin >> b[i];
        }
        ll lo = 0, hi = n - idx;
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            if (counts(idx, mid, pos, b) == mid) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        cout << lo << '\n';
    }

    return 0;
}