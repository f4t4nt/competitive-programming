#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

ll table[30] = {
    100, 75, 60, 50, 45, 40, 36, 32, 29, 26,
     24, 22, 20, 18, 16, 15, 14, 13, 12, 11,
     10,  9,  8,  7,  6,  5,  4,  3,  2,  1
};
ll prefix[31];

ll get_score(ll rank_lo, ll rank_hi) {
    ll sum = prefix[min(30LL, rank_hi)] - prefix[min(30LL, rank_lo)],
        cnt = rank_hi - rank_lo;
    return (sum + cnt - 1) / cnt + 1;
}

bool ok(ll &m, vector<ll> &req) {
    vector<bool> dp(m);
    FOR (i, m) {
        ll posi = m - i - 1;
        if (req[i] <= get_score(posi, m)) {
            dp[i] = true;
        }
        if (!dp[i]) {
            continue;
        }
        for (ll j = m - 1; j > i; j--) {
            ll posj = m - j - 1, score = get_score(posj, posi);
            if (req[j] <= score) {
                dp[j] = true;
            }
            if (score == 1) {
                break;
            }
        }
    }
    return dp[m - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    FOR (i, 30) {
        prefix[i + 1] = prefix[i] + table[i];
    }

    ll n, m;
    cin >> n >> m;
    n--;
    vector<vector<ll>> raw(m, vector<ll>(n));
    FOR (i, m) {
        FOR (j, n) {
            cin >> raw[i][j];
        }
    }
    FOR (i, m) {
        rsort(raw[i]);
    }
    ll my/*-tien, she dgaf lil bro ._.*/ = 0;
    FOR (i, min(4LL, n)) {
        my += raw[0][i];
    }
    vector<ll> req;
    FOB (i, 1, m) {
        ll cur = 0;
        FOR (j, min(4LL, n)) {
            cur += raw[i][j];
        }
        if (cur > my) {
            req.pb(0);
        } else {
            cur = 0;
            FOR (j, min(3LL, n)) {
                cur += raw[i][j];
            }
            req.pb(1 + my - cur);
        }
    }
    ssort(req);
    ll lo = 0, hi = m - 1;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (ok(mid, req)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo + 1 << '\n';

    return 0;
}