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
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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

ll dist2(pair<ll, ll> a, pair<ll, ll> b) {
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) * (a.second - b.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> p(n);
    FOR (i, n) {
        cin >> p[i].first >> p[i].second;
    }
    ssort(p);
    set<pair<ll, ll>> active;
    ll rv = LLONG_MAX;
    ll j = 0;
    FOR (i, n) {
        ll r = ceil(sqrt(rv));
        while (j < i && p[j].first < p[i].first - r) {
            active.erase({p[j].second, p[j].first});
            j++;
        }
        auto it = active.lower_bound({p[i].second - r, -LLONG_MAX});
        while (it != active.end() && it->first <= p[i].second + r) {
            rv = min(rv, dist2(p[i], {it->second, it->first}));
            it++;
        }
        active.insert({p[i].second, p[i].first});
    }
    cout << rv << '\n';

    return 0;
}