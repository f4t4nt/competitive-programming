#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long long ld;
typedef complex<ld> cd;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) ssort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ll t; cin >> t;
    while (t--) {
        ll a, b, m; cin >> a >> b >> m;
        // ll c = (b + a - 1) / a;
        // ll strat[2] = {
        //     2 + m / b * (b / a + 1) + (m % b) / a,
        //     2 + m / (c * a) * (c + 1) + (m % (c * a)) / a
        // };
        // cout << 160 * max(strat[0], strat[1]) << '\n';
        ll c = (b + a - 1) / a * a;
        vector<ll> dp(m + 1, 2);
        FOR (i, m + 1) {
            bool ok = false;
            if (i + b <= m) {
                ok = true;
                dp[i + b] = max(dp[i + b], dp[i] + b / a + 1);
            }
            if (i + c <= m) {
                ok = true;
                dp[i + c] = max(dp[i + c], dp[i] + c / a + 1);
            }
            if (!ok) {
                ll d = m - i;
                dp[i + d] = max(dp[i + d], dp[i] + d / a);
            }
        }
        cout << 160 * *max_element(all(dp)) << '\n';
    }
    return 0;
}