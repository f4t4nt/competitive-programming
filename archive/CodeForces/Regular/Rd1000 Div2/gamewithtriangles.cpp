#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define x first
// #define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

vector<ll> buildPairSum(vector<ll> &arr) {
    ll n = sz(arr);
    ll mx = n / 2;
    vector<ll> res(mx + 1, 0LL);
    FOR1 (x, mx + 1) {
        res[x] = res[x - 1] + arr[n - x] - arr[x - 1];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<ll> a(n), b(m);
        FOR (i, n) cin >> a[i];
        FOR (j, m) cin >> b[j];
        ssort(a), ssort(b);
        vector<ll> ca = buildPairSum(a), cb = buildPairSum(b);
        ll kmax = min({n, m, (n + m) / 3LL});
        if (kmax <= 0) {
            cout << 0 << '\n';
            continue;
        }
        cout << kmax << '\n';
        auto Q = [&](ll k, ll x) {
            return ca[x] + cb[k - x];
        };
        auto dQ = [&](ll k, ll x) {
            return ca[x + 1] - ca[x] + cb[k - x - 1] - cb[k - x];
        };
        ll prvk = 0, xcur = 0;
        vector<ll> ans(kmax + 1, 0LL);
        FOR1 (k, kmax + 1) {
            ll l = max(0LL, 2 * k - m);
            ll r = min(k, n - k);
            if (l > r) {
                ans[k] = 0;
                continue;
            }
            r = min(r, k);
            l = max(l, k - m / 2);
            r = min(r, n / 2);
            if (l > r) {
                ans[k] = 0;
                continue;
            }
            if (xcur < l) xcur = l;
            if (xcur > r) xcur = r;
            bool imp = true;
            while (imp) {
                imp = false;
                while (xcur < r) {
                    if (dQ(k, xcur) > 0) {
                        xcur++;
                        imp = true;
                    } else {
                        break;
                    }
                }
                if (xcur > l) {
                    if (Q(k, xcur - 1) > Q(k, xcur)) {
                        xcur--;
                        imp = true;
                    }
                }
            }
            ans[k] = Q(k, xcur);
        }        
        FOR1 (i, kmax + 1) {
            cout << ans[i];
            if (i < kmax) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}