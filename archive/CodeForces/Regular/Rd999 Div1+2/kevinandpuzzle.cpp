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
    ll,
    null_type,
    less<ll>,
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
// #define x first
// #define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
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

const ll MOD = 998244353;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        vector<ll> a(n + 1);
        FOR (i, n) cin >> a[i + 1];

        ll s_h = (a[1] == 0 ? 1 : 0), s_l = 1;
        if (n == 1) {
            cout << (s_h + s_l) % MOD << '\n';
            continue;
        }

        for (ll i = 2; i <= n; i++) {
            ll new_h = 0;
            if (a[i - 1] == a[i]) {
                new_h = (new_h + s_h) % MOD;
            }
            if (a[i - 2] + 1 == a[i]) {
                new_h = (new_h + s_l) % MOD;
            }
            ll new_l = s_h % MOD;
            s_h = new_h;
            s_l = new_l;
        }

        cout << (s_h + s_l) % MOD << '\n';
    }

    return 0;
}