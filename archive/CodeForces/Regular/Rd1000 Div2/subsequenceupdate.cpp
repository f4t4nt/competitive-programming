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

ll match(vector<ll> &v_out, vector<ll> &v_in) {
    ll diff = 0;
    ll i = 0, j = 0;
    while (i < sz(v_in) && j < sz(v_out)) {
        if (v_out[j] < v_in[i]) {
            diff += (v_out[j] - v_in[i]);
            i++, j++;
        } else {
            i++;
        }
    }
    return diff;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, l, r; cin >> n >> l >> r;
        l--, r--;
        vector<ll> a(n);
        FOR (i, n) cin >> a[i];
        ll seg_sum = 0;
        for (ll i = l; i <= r; i++) {
            seg_sum += a[i];
        }
        vector<ll> v_in, v_left, v_right;
        FOR (i, n) {
            if (i >= l && i <= r) {
                v_in.pb(a[i]);
            } elif (i < l) {
                v_left.pb(a[i]);
            } else {
                v_right.pb(a[i]);
            }
        }
        rsort(v_in);
        ssort(v_left);
        ssort(v_right);
        ll diff1 = 0, diff2 = 0;
        if (!v_left.empty()) {
            diff1 = match(v_left, v_in);
        }
        if (!v_right.empty()) {
            diff2 = match(v_right, v_in);
        }
        ll ans = seg_sum + min({0LL, diff1, diff2});
        cout << ans << '\n';
    }

    return 0;
}