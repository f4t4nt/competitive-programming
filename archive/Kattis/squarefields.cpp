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

bool valid(ll &mid, ll &k, ll &n, vector<pair<ll, ll>> &p) {
    vector<ll> adj(n), clique(1 << n, (1 << n) - 1), dp(1 << n, 1e18);
    FOR (i, n) {
        FOR (j, n) {
            if (max(abs(p[i].first - p[j].first), abs(p[i].second - p[j].second)) <= mid) {
                adj[i] |= (1 << j);
            }
        }
    }
    // {sz of clique, included nodes}
    set<pair<ll, ll>> s;
    FOR (x, 1 << n) {
        ll bitcnt = 0;
        FOR (i, n) {
            if (x & (1 << i)) {
                clique[x] &= adj[i];
                bitcnt++;
            }
        }
        if (x == clique[x]) {
            s.insert({-bitcnt, x});
        }
    }
    dp[0] = 0;
    FORE (x, s) {
        FORR (i, (1 << n)) {
            if (dp[i] != 1e18) {
                dp[i | x.second] = min(dp[i | x.second], dp[i] + 1);
                if (dp[(1 << n) - 1] <= k) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll T;
    cin >> T;
    FOR (t, T) {
        ll n, k;
        cin >> n >> k;
        vector<pair<ll, ll>> p(n);
        FOR (i, n) {
            cin >> p[i].first >> p[i].second;
        }
        ll lo = 1, hi = 64e3;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            if (valid(mid, k, n, p)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        cout << "Case #" << t + 1 << ": " << lo << '\n';
    }

    return 0;
}