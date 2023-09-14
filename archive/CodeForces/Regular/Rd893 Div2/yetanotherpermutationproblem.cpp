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

ll score(ll &n, vector<ll> &perm) {
    set<ll> rv;
    FOR (i, n) {
        rv.insert(__gcd(perm[i], perm[(i + 1) % n]));
    }
    return sz(rv);    
}

pair<ll, vector<ll>> bash(ll &n) {
    vector<ll> perm(n);
    iota(all(perm), 1);
    pair<ll, vector<ll>> rv = {score(n, perm), perm};
    do {
        auto tmp = score(n, perm);
        if (tmp > rv.first) {
            rv = {tmp, perm};
        }
    } while (next_permutation(all(perm)) && perm[0] == 1);
    return rv;
}

pair<ll, vector<ll>> solve(ll &n) {
    vector<bool> used(n + 1);
    vector<ll> perm;
    FOB (i, 1, n + 1) {
        if (used[i]) {
            continue;
        }
        perm.pb(i);
        used[i] = true;
        ll j = 2 * i;
        while (j <= n) {
            while (j <= n && used[j]) {
                j += i;
            }
            if (j > n) {
                break;
            }
            used[j] = true;
            perm.pb(j);
            j *= 2;
        }
    }
    return {score(n, perm), perm};
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
        auto rv = solve(n);
        // cout << rv.first << '\n';
        FORE (x, rv.second) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}