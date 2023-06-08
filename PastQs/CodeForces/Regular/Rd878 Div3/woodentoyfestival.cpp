#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
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

bool valid(ll x, vector<ll> &a) {
    vector<ll> ref = {a[0]};
    FOR (i, sz(a)) {
        if (a[i] - ref.back() > x) {
            ref.pb(a[i]);
            if (sz(ref) > 3) {
                return false;
            }
        }
    }
    return sz(ref) <= 3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        ssort(a);
        ll lo = 0, hi = 1e9;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (valid(mid, a)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        cout << (lo + 1) / 2 << '\n';
        // // dp[i] = {max waiting time, where i begins}
        // vector<pair<ll, ll>> dp0(3, {0, a[0]}), dp1;
        // FOB (i, 1, n) {
        //     dp1 = dp0;
        //     FOR (j, 3) {
        //         dp1[j].first = max(dp0[j].first, (a[i] - dp0[j].second + 1) / 2);
        //     }
        //     FOB (j, 1, 3) {
        //         if (dp0[j - 1].first <= dp1[j].first) {
        //             dp1[j] = {dp0[j - 1].first, a[i]};
        //         }
        //     }
        //     dp0 = dp1;
        // }
        // ll rv = 1e18;
        // FOR (i, 3) {
        //     rv = min(rv, dp0[i].first);
        // }
        // cout << rv << '\n';
    }

    return 0;
}