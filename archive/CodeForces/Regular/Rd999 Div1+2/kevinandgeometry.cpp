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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        map<ll, ll> cnt;
        FOR (i, n) {
            ll a; cin >> a;
            cnt[a]++;
        }
        ll a = -1, b = -1, c = -1;
        for (auto it = cnt.rbegin(); it != cnt.rend(); it++) {
            if (it->second >= 2) {
                a = it->first;
                it->second -= 2;
                if (it->second == 0) {
                    cnt.erase(it->first);
                }
                break;
            }
        }
        ll min_diff = LLONG_MAX;
        for (auto [k, v] : cnt) {
            if (v >= 2) {
                b = c = k;
                min_diff = 0;
                break;
            }
        }
        if (min_diff > 0) {
            auto cur = cnt.begin(), nxt = next(cur);
            while (nxt != cnt.end()) {
                if (nxt->first - cur->first < min_diff) {
                    min_diff = nxt->first - cur->first;
                    b = cur->first;
                    c = nxt->first;
                }
                cur++, nxt++;
            }
        }
        if (min({a, b, c}) == -1 || b + 2 * a <= c) {
            cout << -1 << '\n';
        } else {
            cout << a << ' ' << a << ' ' << b << ' ' << c << '\n';
        }
    }

    return 0;
}