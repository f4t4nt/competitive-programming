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

ll pow10[19];

void bash(ll n, vector<ll> &cnt) {
    FOB (i, 1, n + 1) {
        ll x = i;
        while (x) {
            cnt[x % 10]++;
            x /= 10;
        }
    }
    FOR (i, 10) {
        assert(cnt[1] >= cnt[i]);
    }
}

ll cnt1(ll n) {
    // vector<ll> ref(10);
    // bash(n, ref);
    ll rv = 0, m = 0;
    for (ll i = 0; n; i++) {
        ll d = n % 10;
        n /= 10;
        if (d == 1) {
            rv += n * pow10[i] + m + 1;
        } elif (d > 1) {
            rv += (n + 1) * pow10[i];
        } else {
            rv += n * pow10[i];
        }
        m += d * pow10[i];
    }
    // assert(rv == ref[1]);
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    pow10[0] = 1;
    FOB (i, 1, 19) {
        pow10[i] = pow10[i - 1] * 10;
    }

    ll n, lo = 1, hi = 1e18;
    cin >> n;
    while (lo + 1 < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (cnt1(mid) > n) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    cout << lo << '\n';

    return 0;
}