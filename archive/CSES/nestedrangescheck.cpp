#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
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
 
vector<pair<ll, ll>> idx_set_conv(indexed_set &s) {
    vector<pair<ll, ll>> rv;
    FORE (x, s) {
        rv.pb(x);
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n;
    cin >> n;
    vector<pair<ll, ll>> ranges(n);
    vector<tuple<ll, ll, ll>> events;
    FOR (i, n) {
        ll x, y;
        cin >> x >> y;
        ranges[i] = {x, y};
        // long starting come first
        events.pb({x, x - y, i});
        // long ending come last
        events.pb({y, y - x, i});
    }
    ssort(events);
    vector<ll> rv0(n, -1), rv1(n, -1);
    ll sz_ended = 0, sz_active = 0;
    indexed_set ended, active;
    FORE (event, events) {
        auto [x, len, i] = event;
        if (len < 0) { // starting
            active.insert({ranges[i].first, i});
            sz_active++;
        } else { // ending
            // how many in ended started after me? -> how many i contain
            rv0[i] = sz_ended - ended.order_of_key({ranges[i].first, -1});
            active.erase({ranges[i].first, i});
            sz_active--;
            ended.insert({ranges[i].first, i});
            sz_ended++;
            // how many in active started before me? -> how many contain me
            rv1[i] = active.order_of_key({ranges[i].first, 1e9});
        }
    }
    FORE (x, rv0) {
        // cout << x << ' ';
        cout << (x ? 1 : 0) << ' ';
    }
    cout << '\n';
    FORE (x, rv1) {
        // cout << x << ' ';
        cout << (x ? 1 : 0) << ' ';
    }
    cout << '\n';

    return 0;
}