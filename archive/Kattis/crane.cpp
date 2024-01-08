#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

bool do_flip(ll l, ll r, ll &del, vector<ll> &a, vector<pair<ll, ll>> &rv) {
    assert(l <= r);
    if ((r - l) % 2 == 0) return false;
    if (l < 0 || r >= sz(a)) return false;
    rv.pb({l, r});
    del = (r - l + 1) / 2;
    FOB (i, l, l + del) swap(a[i], a[i + del]);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n);
        FOR (i, n) cin >> a[i], a[i]--;
        ll k = 0, del;
        vector<pair<ll, ll>> rv;
        while (k != n) {
            while (a[k] == k && k != n) k++;
            if (k != n) {
                ll kdx = 0;
                FOB (i, k, n) if (a[i] == k) {
                    kdx = i;
                    break;
                }
                if (kdx > (n + k) / 2) {
                    assert(do_flip(k, n - 1, del, a, rv) ||
                            do_flip(k + 1, n - 1, del, a, rv));
                    kdx -= del;
                }
                assert(do_flip(k, kdx * 2 - k, del, a, rv) ||
                        do_flip(k, kdx * 2 - k - 1, del, a, rv));
            }
        }
        FOR (i, n) assert(a[i] == i);
        cout << sz(rv) << '\n';
        for (auto [l, r] : rv) cout << l + 1 << ' ' << r + 1 << '\n';
    }

    return 0;
}