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

void find_ref(ll &n, ll &k, vector<ll> &a, vector<ll> &ref) {
    FORR (i, n) {
        ref[a[i]] = i;
    }
    FORR (i, k - 1) {
        ref[i] = min(ref[i], ref[i + 1]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n), a_copy;
        vector<bool> ok(k);
        FOR (i, n) {
            cin >> a[i];
            a[i]--;
            ok[a[i]] = true;
        }
        a_copy = a;
        vector<ll> ref0(k, 1e18), ref1(k, 1e18), rv(k);
        find_ref(n, k, a, ref0);
        flip(a_copy);
        find_ref(n, k, a_copy, ref1);
        FOR (i, k) {
            ref1[i] = n - ref1[i];
            if (ok[i]) {
                rv[i] = 2 * (ref1[i] - ref0[i]);
            }
        }
        FORE (x, rv) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}