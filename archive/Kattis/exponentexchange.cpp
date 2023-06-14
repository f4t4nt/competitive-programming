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

constexpr ll INF = 1e18;

vector<pair<ll, ll>> combine(
    vector<vector<pair<ll, ll>>> &dp,
    ll &b,
    ll &shift
) {
    ll  i0 = 0, i1 = 0, last = -1, curr_min = INF;
    vector<pair<ll, ll>> rv;
    while (i0 < sz(dp[0]) || i1 < sz(dp[1])) {
        while (i0 < sz(dp[0]) && dp[0][i0].second < last) {
            i0++;
        }
        while (i1 < sz(dp[1]) && dp[1][i1].second + shift < last) {
            i1++;
        }
        pair<ll, ll> x,
            x0 = {INF, INF},
            x1 = {INF, INF};
        if (i0 < sz(dp[0])) {
            x0 = {dp[0][i0].first + b - shift, dp[0][i0].second};
        }
        if (i1 < sz(dp[1])) {
            x1 = {dp[1][i1].first, max(0LL, dp[1][i1].second + shift)};
        }
        if (x0.second < x1.second) {
            x = x0;
            i0++;
        } elif (x0.second > x1.second) {
            x = x1;
            i1++;
        } else {
            x = min(x0, x1);
            i0++;
            i1++;
        }
        if (x.first < curr_min) {
            curr_min = x.first;
            last = x.second;
            rv.pb(x);
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll b, p;
    cin >> b >> p;
    vector<ll> a(p);
    FOR (i, p) {
        cin >> a[i];
    }

    vector<vector<pair<ll, ll>>> dp0(2, {{0,0}});
    FOR (i, p) {
        vector<vector<pair<ll, ll>>> dp1(2);
        FOR (j, 2) {
            ll tmp = a[i] + 1 - j;
            dp1[j] = combine(dp0, b, tmp);
        }
        dp0 = dp1;
    }

    ll rv = INF;
    FORE (x, dp0[1]) {
        rv = min(rv, max(x.first, x.second));
    }
    cout << rv << '\n';

    return 0;
}