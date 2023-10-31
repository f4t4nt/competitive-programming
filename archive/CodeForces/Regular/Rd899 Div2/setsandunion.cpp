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

// imma show YOU how great i am.

ll eval(set<ll> rem, map<ll, set<ll>> cnt) {
    ll rv = 0;
    FORE (e, cnt) {
        bool is_subset = true;
        FORE (f, e.second) {
            if (rem.find(f) == rem.end()) {
                is_subset = false;
                break;
            }
        }
        if (!is_subset) {
            rv++;
        }
    }
    return rv;
}

void solve() {
    ll n;
    cin >> n;
    map<ll, set<ll>> cnt;
    vector<set<ll>> S(n);
    FOR (i, n) {
        ll k;
        cin >> k;
        FOR (j, k) {
            ll x;
            cin >> x;
            S[i].insert(x);
            cnt[x].insert(i);
        }
    }
    ll rv = 0;
    FORE (e, cnt) {
        rv = max(rv, eval(e.second, cnt));
    }
    cout << rv << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}