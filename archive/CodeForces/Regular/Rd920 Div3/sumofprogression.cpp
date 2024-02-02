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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t; cin >> t;
    while (t--) {
        ll n, q; cin >> n >> q;
        vector<ll> a(n), rv(q);
        FOR (i, n) cin >> a[i];
        // {d, s%d} : {s, k, qdx}
        map<pair<ll, ll>, vector<tuple<ll, ll, ll>>> m;
        FOR (qdx, q) {
            ll s, d, k; cin >> s >> d >> k;
            s--;
            m[{d, s % d}].pb({s, k, qdx});
        }
        vector<ll> pre0(n + 1), pre1(n + 1);
        for (auto [k, v] : m) {
            auto [d, r] = k;
            if (sz(v) > 2) {
                ll i = 1;
                for (ll idx = r; idx < n; idx += d) {
                    pre0[i] = pre0[i - 1] + a[idx];
                    pre1[i] = pre1[i - 1] + a[idx] * i;
                    i++;
                }
                for (auto [s, k, qdx] : v) {
                    ll lo = (s - r) / d,
                        hi = lo + k;
                    ll cv = pre1[hi] - pre1[lo] - (pre0[hi] - pre0[lo]) * lo;
                    rv[qdx] = cv;
                }
            } else {
                for (auto [s, k, qdx] : v) {
                    ll cv = 0, idx = s;
                    FOR (i, k) {
                        cv += a[idx] * (i + 1);
                        idx += d;
                    }
                    rv[qdx] = cv;
                }
            }
        }
        FORE (v, rv) cout << v << ' ';
        cout << '\n';
    }

    return 0;
}