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

ll table[30] = {
    100, 75, 60, 50, 45, 40, 36, 32, 29, 26,
     24, 22, 20, 18, 16, 15, 14, 13, 12, 11,
     10,  9,  8,  7,  6,  5,  4,  3,  2,  1
};
ll prefix[31];

ll get_score(ll rank_lo, ll rank_hi) {
    ll sum = prefix[min(30LL, rank_hi)] - prefix[min(30LL, rank_lo)],
        cnt = rank_hi - rank_lo;
    return (sum + cnt - 1) / cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    FOR (i, 30) {
        prefix[i + 1] = prefix[i] + table[i];
    }

    ll n;
    cin >> n;
    // {-problems, penalty, last solve, id}
    vector<tuple<ll, ll, ll, ll>> scores(n);
    vector<ll> bonus(n), rv(n);
    FOR (i, n) {
        ll s, p, f;
        cin >> s >> p >> f >> bonus[i];
        scores[i] = {-s, p, f, i};
    }
    ssort(scores);
    tuple<ll, ll, ll> prev_score = {1e18, 1e18, 1e18};
    ll prev, cur = 0;
    FOR (i, n) {
        auto [s, p, f, id] = scores[i];
        if (tie(s, p, f) != prev_score) {
            if (i > 0) {
                ll score = get_score(prev, i);
                FOB (j, prev, i) {
                    ll jd = get<3>(scores[j]);
                    rv[jd] = score + bonus[jd];
                }
            }
            prev_score = {s, p, f};
            prev = i;
        }
    }
    ll score = get_score(prev, n);
    FOB (j, prev, n) {
        ll jd = get<3>(scores[j]);
        rv[jd] = score + bonus[jd];
    }
    FORE (x, rv) {
        cout << x << '\n';
    }

    return 0;
}