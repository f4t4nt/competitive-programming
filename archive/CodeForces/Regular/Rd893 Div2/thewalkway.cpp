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

ll solve(ll &n, ll &m, ll &d, vector<pair<ll, ll>> &s) {
    pair<ll, ll> rv = {0, 0};
    FOR (i, m) {
        rv.first += (s[i].first - rv.second) / d;
        if ((s[i].first - rv.second) % d != 0) {
            rv.first += s[i].second;
        }
        rv.second = s[i].first;
    }
    return rv.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m, d;
        cin >> n >> m >> d;
        vector<pair<ll, ll>> s(m + 2);
        s[0] = {1, 1}, s[m + 1] = {n, 0};
        FOR (i, m) {
            cin >> s[i + 1].first;
            s[i + 1].second = 1;
        }
        m += 2;
        ll ref = solve(n, m, d, s);
        pair<ll, ll> rv = {1e18, -1};
        FOB (i, 1, m - 1) {
            ll cur_cost = (s[i + 1].first - s[i].first) / d + (s[i].first - s[i - 1].first) / d;
            if ((s[i + 1].first - s[i].first) % d != 0) {
                cur_cost += s[i + 1].second;
            }
            if ((s[i].first - s[i - 1].first) % d != 0) {
                cur_cost += s[i].second;
            }
            ll new_cost = (s[i + 1].first - s[i - 1].first) / d;
            if ((s[i + 1].first - s[i - 1].first) % d != 0) {
                new_cost += s[i + 1].second;
            }
            ll new_tot = ref - cur_cost + new_cost;
            if (new_tot < rv.first) {
                rv = {new_tot, 1};
            } elif (new_tot == rv.first) {
                rv.second++;
            }
        }
        cout << rv.first << ' ' << rv.second << '\n';
    }

    return 0;
}