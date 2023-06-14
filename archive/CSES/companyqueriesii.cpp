#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

ll check_depth(ll d, vector<ll> &nodes, vector<pair<ll, ll>> &ranges, pair<ll, ll> &ref) {
    ll lo = 0, hi = sz(nodes) - 1;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (ranges[nodes[mid]].first <= ref.first) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    if (ranges[nodes[lo]].first <= ref.first &&
        ranges[nodes[lo]].second >= ref.second) {
        return nodes[lo];
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<ll> e(n), depth(n);
    vector<vector<ll>> children(n);

    e[0] = -1;
    FOB (i, 1, n) {
        cin >> e[i];
        e[i]--;
        children[e[i]].pb(i);
    }

    vector<pair<ll, ll>> ranges(n);
    ll t = 0;
    function<void(ll)> dfs = [&](ll v) {
        ranges[v].first = t++;
        FORE (u, children[v]) {
            depth[u] = depth[v] + 1;
            dfs(u);
        }
        ranges[v].second = t;
    };
    dfs(0);

    vector<vector<ll>> depths(n);
    FOR (i, n) {
        depths[depth[i]].pb(i);
    }

    FOR (i, n) {
        sort(depths[i].begin(), depths[i].end(), [&](ll a, ll b) {
            return ranges[a].first < ranges[b].first;
        });
    }

    while (q--) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        if (depth[a] < depth[b]) {
            swap(a, b);
        }
        pair<ll, ll> ref = {
            min(ranges[a].first, ranges[b].first),
            max(ranges[a].second, ranges[b].second)
        };
        // ll rv = -1;
        // FORR (i, depth[a] + 1) {
        //     // FOR (v, sz(depths[i])) {
        //     //     if (ranges[depths[i][v]].first <= ref.first &&
        //     //         ranges[depths[i][v]].second >= ref.second) {
        //     //         rv = depths[i][v];
        //     //         break;
        //     //     }
        //     // }
        //     // if (rv != -1) {
        //     //     break;
        //     // }
        //     rv = check_depth(i, depths[i], ranges, ref);
        //     if (rv != -1) {
        //         break;
        //     }
        // }
        ll lo = 0, hi = depth[a];
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            if (check_depth(mid, depths[mid], ranges, ref) != -1) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        ll rv = check_depth(lo, depths[lo], ranges, ref);
        cout << rv + 1 << '\n';
    }

    return 0;
}