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
// #define f first
// #define s second

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

ld solve(ll &n, vector<ld> &v) {
    vector<pair<ld, ll>> ref;
    FORR (i, n) {
        ref.pb({v[i], 1});
        while (sz(ref) > 1 && ref[sz(ref) - 2].first <= ref[sz(ref) - 1].first) {
            ref[sz(ref) - 2].first = (ref[sz(ref) - 2].first * ref[sz(ref) - 2].second + ref[sz(ref) - 1].first * ref[sz(ref) - 1].second) /
                (ref[sz(ref) - 2].second + ref[sz(ref) - 1].second);
            ref[sz(ref) - 2].second += ref[sz(ref) - 1].second;
            ref.pop_back();
        }
    }
    vector<ld> conv;
    FORR (i, sz(ref)) FOR (j, ref[i].second) conv.pb(ref[i].first);
    ld rv = 0;
    FOR (i, n) rv += (v[i] - conv[i]) * (v[i] - conv[i]);
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n; cin >> n;
    vector<ld> x(n), y(n);
    FOR (i, n) cin >> x[i] >> y[i];
    ld rvx = solve(n, x), rvy = solve(n, y), rv = rvx + rvy;
    cout << fixed << setprecision(10) << rv << '\n';

    return 0;
}