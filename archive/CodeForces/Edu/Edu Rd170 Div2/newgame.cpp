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
        ll n, k; cin >> n >> k;
        vector<ll> a(n);
        map<ll, ll> cnt_map;
        FOR (i, n) {
            cin >> a[i];
            cnt_map[a[i]]++;
        }
        vector<ll> unq, cnt;
        for (auto& p : cnt_map) {
            unq.pb(p.first);
            cnt.pb(p.second);
        }
        ll m = unq.size(), res = 0, l = 0;
        while (l < m) {
            ll r = l;
            while (r + 1 < m && unq[r + 1] == unq[r] + 1) {
                r++;
            }
            ll len = r - l + 1;
            vector<ll> seg_cnt(cnt.begin() + l, cnt.begin() + r + 1);
            ll sum = 0, start = 0;
            FOR (end, len) {
                sum += seg_cnt[end];
                while (end - start + 1 > k) {
                    sum -= seg_cnt[start];
                    start++;
                }
                if (sum > res) res = sum;
            }
            l = r + 1;
        }
        cout << res << '\n';
    }

    return 0;
}