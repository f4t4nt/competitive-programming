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
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> segs(n);
        FOR (i, n) {
            cin >> segs[i].first >> segs[i].second;
        }
        ssort(segs);
        vector<ll> dp(n + 1);
        FORR (i, n) {
            dp[i] = dp[i + 1];
            ll hi = 1e18;
            FOB (j, i + 1, n) {
                if (segs[j].first <= segs[i].second) {
                    hi = min(hi, segs[j].second);
                }
            }
            if (hi == 1e18) {
                continue;
            }
            ll j = i;
            while (j < n && segs[j].first <= max(segs[i].second, hi)) {
                j++;
            }
            dp[i] = max(dp[i], 1 + dp[j]);
        }
        cout << n - 2 * dp[0] << '\n';
    }

    return 0;
}