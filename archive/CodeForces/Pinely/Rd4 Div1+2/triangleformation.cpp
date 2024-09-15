#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool eval3(vector<ll> c) {
    return (
        c[0] + c[1] > c[2] &&
        c[0] + c[2] > c[1] &&
        c[1] + c[2] > c[0]
    );
}

bool eval6(vector<ll> c) {
    return (
        c[0] + c[1] > c[2] &&
        c[0] + c[2] > c[1] &&
        c[1] + c[2] > c[0] &&
        c[3] + c[4] > c[5] &&
        c[3] + c[5] > c[4] &&
        c[4] + c[5] > c[3]
    );
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    FOR (i, n) cin >> a[i];
    while (q--) {
        ll l, r; cin >> l >> r; l--;
        if (r - l > 47) cout << "YES\n";
        else {
            vector<ll> b;
            for (ll i = l; i < r; i++) b.pb(a[i]);
            ssort(b);
            ll ok = 0;
            ll i = 0;
            while (ok < 2 && i < sz(b) - 5) {
                if (
                    eval6({b[i], b[i+3], b[i+2], b[i+1], b[i+4], b[i+5]}) ||
                    eval6({b[i], b[i+3], b[i+4], b[i+1], b[i+2], b[i+5]}) ||
                    eval6({b[i], b[i+4], b[i+5], b[i+1], b[i+2], b[i+3]})
                ) ok = 2;
                i++;
            }
            i = 0;
            while (ok < 2 && i < sz(b) - 2) {
                if (eval3({b[i], b[i+1], b[i+2]})) {
                    ok++;
                    i += 2;
                }
                i++;
            }
            cout << (ok == 2 ? "YES\n" : "NO\n");
        }
    }
    
    return 0;
}