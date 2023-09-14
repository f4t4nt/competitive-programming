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

void init_dp(
    ll &n,
    vector<pair<ll, ll>> &movies,
    set<tuple<ll, ll, ll>> time_s,
    set<tuple<ll, ll, ll>> time_e,
    vector<vector<ll>> &dp
) {
    FOR (i, n) {
        while (sz(time_s) && get<0>(*time_s.begin()) < movies[i].first) {
            auto [s, e, idx] = *time_s.begin();
            time_s.erase(time_s.begin());
            time_e.erase({e, s, idx});
        }
        auto [e, s, idx] = *time_e.begin();
        dp[i][0] = idx;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> movies(n);
    set<tuple<ll, ll, ll>> time_s, time_e;
    FOR (i, n) {
        cin >> movies[i].second >> movies[i].first;
    }
    ssort(movies);
    movies.pb({1e9, 1e9});
    FOR (i, n) {
        time_s.insert({movies[i].second, movies[i].first, i});
        time_e.insert({movies[i].first, movies[i].second, i});
    }
    time_s.insert({1e9, 1e9, n});
    time_e.insert({1e9, 1e9, n});
    n++;
    vector<vector<ll>> dp(n, vector<ll>(30, n));
    init_dp(n, movies, time_s, time_e, dp);
    FOR (j, 29) {
        FOR (i, n) {
            dp[i][j + 1] = dp[dp[i][j]][j];
        }
    }
    // {start, idx}
    vector<pair<ll, ll>> ref;
    FOR (i, n) {
        if (sz(ref) == 0 || ref.back().first < movies[i].second) {
            ref.pb({movies[i].second, i});
        }
    }
    while (q--) {
        ll a, b, rv = 0;
        cin >> a >> b;
        auto it = lower_bound(all(ref), make_pair(a, 0LL));
        auto [s, idx] = *it;
        if (movies[idx].first > b) {
            cout << 0 << '\n';
            continue;
        }
        FORR (i, 30) {
            if (movies[dp[idx][i]].first <= b) {
                idx = dp[idx][i];
                rv += (1 << i);
            }
        }
        cout << rv + 1 << '\n';
    }

    return 0;
}