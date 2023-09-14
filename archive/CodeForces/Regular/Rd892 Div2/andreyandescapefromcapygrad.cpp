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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<vector<ll>> portals(n, vector<ll>(4));
        vector<pair<ll, ll>> events;
        FOR (i, n) {
            FOR (j, 4) { // {l, r, a, b}
                cin >> portals[i][j];
            }
            // {b, l}
            // {b, i + 1} - new portal i has right end at b
            // {l, -(i + 1)} - active range i has left end at l
            events.pb({portals[i][3], i + 1});
            events.pb({portals[i][0], -(i + 1)});
        }
        rsort(events); // process new portals first
        set<pair<ll, ll>> active; // {b, i}
        vector<ll> mx(n);
        FOR (i, n) {
            mx[i] = portals[i][3];
        }
        map<ll, ll> ref; // max place each pos can go, if -1 then stay put
        FORE (event, events) {
            auto [x, i] = event;
            if (i > 0) { // right end of new portal
                i--;
                if (active.empty() && !ref.count(x + 1)) {
                    ref[x + 1] = -1; // beyond this pos, there is no range
                }
                active.insert({portals[i][3], i});
                // find max of available portals
                ll max_b = active.rbegin()->first;
                ref[portals[i][0]] = max_b;
                active.erase({portals[i][3], i});
                active.insert({max_b, i});
                mx[i] = max_b;
            } else { // left end of active range
                i = -i - 1;
                active.erase({mx[i], i});
            }
        }
        ref[0] = -1;
        ll q;
        cin >> q;
        while (q--) {
            ll x, rv;
            cin >> x;
            auto it = ref.upper_bound(x);
            it--;
            if (it->second == -1) {
                rv = x;
            } else {
                rv = it->second;
            }
            cout << rv << ' ';
        }
        cout << '\n';
    }

    return 0;
}