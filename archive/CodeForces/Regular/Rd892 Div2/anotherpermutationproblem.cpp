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

ll score(vector<ll> &perm) {
    ll rv = 0;
    pair<ll, ll> mx = {0, -1};
    FOR (i, sz(perm)) {
        rv += perm[i] * (i + 1);
        mx = max(mx, {perm[i] * (i + 1), i});
    }
    rv -= mx.first;
    return rv;
}

pair<ll, vector<ll>> bash(ll n) {
    vector<ll> perm(n);
    iota(all(perm), 1);
    pair<ll, vector<ll>> rv = {0, {}};
    do {
        rv = max(rv, {score(perm), perm});
    } while (next_permutation(all(perm)));
    return rv;
}

pair<ll, vector<ll>> score(vector<ll> &perm0, vector<ll> &perm1) {
    vector<ll> perm = perm0;
    perm.insert(perm.end(), all(perm1));
    return {score(perm), perm};
}

pair<ll, vector<ll>> solve(ll n) {
    vector<ll> perm0(n), perm1;
    iota(all(perm0), 1);
    pair<ll, vector<ll>> rv = {score(perm0), perm0};
    while (sz(perm0)) {
        perm1.pb(perm0.back());
        perm0.pop_back();
        rv = max(rv, score(perm0, perm1));
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        // auto [s, p] = bash(n);
        auto [s, p] = solve(n);
        cout << s << '\n';
        // FORE (x, p) {
        //     cout << x << ' ';
        // }
        // cout << '\n';
    }

    return 0;
}