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

ll bitcount(ll x) {
    ll rv = 0;
    while(x > 0) {
        rv++;
        x &= (x - 1);
    }
    return rv;
}

ld dist(ld dx, ld dy) {
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pair<ld, ld> roost;
    cin >> roost.first >> roost.second;
    ll n;
    cin >> n;
    vector<pair<ld, ld>> spots(n);
    FOR (i, n) {
        cin >> spots[i].first >> spots[i].second;
    }
    if (n % 2 == 1) {
        spots.pb(roost);
        n++;
    }
    vector<ld> dp(1 << n, 1e18);
    dp[0] = 0;
    FOR (i, 1 << n) {
        ll cnt = bitcount(i);
        if (cnt % 2 == 1) {
            continue;
        }
        set<ll> s;
        FOR (j, n) {
            if (i & (1 << j)) {
                s.insert(j);
            }
        }
        ll tmp = (i != (1 << n) - 1 ? 1 : 0);
        FORE (j, s) {
            // roost -> spot[j] -> roost
            // dp[i] = min(dp[i], dp[i ^ (1 << j)] + dist(spots[j].first - roost.first, spots[j].second - roost.second) * (1 + tmp));
            FORE (k, s) {
                if (j >= k) {
                    dp[i] = min(dp[i], dp[i ^ (1 << j) ^ (1 << k)] + min(
                        // roost -> spot[j] -> spot[k] -> roost
                        dist(spots[j].first - roost.first, spots[j].second - roost.second) +
                        dist(spots[j].first - spots[k].first, spots[j].second - spots[k].second) +
                        dist(spots[k].first - roost.first, spots[k].second - roost.second) * tmp,
                        // roost -> spot[k] -> spot[j] -> roost
                        dist(spots[k].first - roost.first, spots[k].second - roost.second) +
                        dist(spots[k].first - spots[j].first, spots[k].second - spots[j].second) +
                        dist(spots[j].first - roost.first, spots[j].second - roost.second) * tmp
                    ));
                }
            }
        }
    }
    cout << fixed << setprecision(10) << dp[(1 << n) - 1] << '\n';

    return 0;
}