#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()

const ll INF = 4e18;

// -----------------------------------------------------------------------------
//  Longest Increasing Subsequence
// -----------------------------------------------------------------------------
//  Returns:    one longest strictly increasing subsequence of a
//  Notes:      - d[j] = smallest tail of an increasing subsequence of length j
//  Complexity: O(n log n)
// -----------------------------------------------------------------------------
vector<ll> lis(vector<ll> &a) {
    ll n = sz(a);
    vector<ll> d(n + 1, INF), p(n, 0);
    d[0] = -INF;
    for (ll i = 0; i < n; i++) {
        ll j = upper_bound(all(d), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            p[i] = j;
        }
    }
    ll len = 0;
    for (ll i = 0; i <= n; i++) if (d[i] < INF) len = i;
    vector<ll> ans(len);
    for (ll i = n - 1; len && i >= 0; i--) if (p[i] == len) ans[--len] = a[i];
    return ans;
}
