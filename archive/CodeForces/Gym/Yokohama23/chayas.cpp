#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

const ll MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<tuple<ll, ll, ll>> conds(m);
    bitset<1LL << 24> invalid;
    FOR (i, m) {
        ll a, b, c; cin >> a >> b >> c;
        a--, b--, c--;
        conds[i] = {a, b, c};
    }
    FOR (i, (1LL << n)) {
        for (auto [a, b, c] : conds) {
            ll ac = (1LL << a) | (1LL << c);
            if ((i & (1LL << b)) == 0) {
                if ((i & ac) == ac) {
                    invalid[i] = 1;
                }
            } else {
                if ((i & ac) == 0) {
                    invalid[i] = 1;
                }
            }
            if (invalid[i]) break;
        }
    }
    vector<ll> dp(1LL << n);
    dp[0] = 1;
    FOR (i, (1LL << n)) {
        if (invalid[i]) continue;
        FOR (j, n) {
            if (i & (1LL << j)) {
                ll prv = i ^ (1LL << j);
                dp[i] = (dp[i] + dp[prv]) % MOD;
            }
        }
    }
    cout << dp.back() << '\n';

    return 0;
}