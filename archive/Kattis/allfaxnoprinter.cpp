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

vector<ll> actual(ll &n, ll &k, vector<pair<ll, ll>> &events) {
    ll cur = 0;
    vector<ll> rv;
    // {end time, id}
    set<pair<ll, ll>> s;
    FOR (i, n) {
        while (!s.empty() && s.begin()->first <= events[i].first) {
            s.erase(s.begin());
            cur++;
        }
        if (sz(s) < k) {
            s.insert({events[i].first + events[i].second, i});
        }
        rv.pb(cur + sz(s));
    }
    return rv;
}

vector<ll> ideal(ll &n, ll &k, vector<pair<ll, ll>> &events) {
    ll cur = 0;
    vector<ll> rv;
    // {end time, id}
    set<pair<ll, ll>> s;
    FOR (i, n) {
        while (!s.empty() && s.begin()->first <= events[i].first) {
            s.erase(s.begin());
            cur++;
        }
        s.insert({events[i].first + events[i].second, i});
        while (sz(s) > k) {
            s.erase(prev(s.end()));
        }
        rv.pb(cur + sz(s));
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> events(n);
    FORE (e, events) {
        cin >> e.first >> e.second;
    }
    auto rv0 = actual(n, k, events), rv1 = ideal(n, k, events);
    FOR (i, n) {
        cout << rv1[i] - rv0[i] << '\n';
    }

    return 0;
}