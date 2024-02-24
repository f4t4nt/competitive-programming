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
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

#define x first
#define y second

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    // 0: horizontal leaving
    // 1: vertical leaving
    // 2: horizontal entering
    // 3: vertical entering
    // update ans on 3
    multiset<pll> events;
    FOR (i, n) {
        ch c; ll t, m, a;
        cin >> c >> t >> m >> a;
        ll p0 = -t + a + 1, p1 = -t - m + a + 1;
        if (c == 'h') {
            events.insert({p0, 0});
            events.insert({p1, 2});
        } else {
            events.insert({p0, 1});
            events.insert({p1, 3});
        }
    }
    ll v_cnt = 0, h_cnt = 0, ans = 0;
    for (auto [p, t] : events) {
        if (t == 0) h_cnt--;
        elif (t == 1) v_cnt--;
        elif (t == 2) {
            h_cnt++;
            ans += v_cnt;
        } else {
            v_cnt++;
            ans += h_cnt;
        }
    }
    cout << ans << '\n';

    return 0;
}