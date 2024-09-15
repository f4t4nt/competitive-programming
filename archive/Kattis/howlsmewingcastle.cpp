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
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll ZERO = 4e6;
const ll MAX = 23;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<ll> a(n);
    FOR (i, n) cin >> a[i];
    set<ll> tmp(all(a));
    if (sz(tmp) != sz(a) || tmp.count(0) || n > MAX) {
        cout << 0 << '\n';
        return 0;
    }

    vector<bitset<8000001>> dp(MAX + 1);
    dp[0][ZERO] = 1;
    FOR (i, n) {
        FORR (j, MAX) {
            dp[j + 1] |= (dp[j] << a[i]);
            dp[j + 1] |= (dp[j] >> a[i]);
        }
        FOR (j, MAX) if (dp[j + 1][ZERO]) {
            cout << 0 << '\n';
            return 0;
        }
    }

    ll ans = MAX;
    vector<ll> ref(ZERO + 1);
    iota(all(ref), 0);
    stable_sort(all(ref), [&](ll x, ll y) {
        return __builtin_popcountll(x) < __builtin_popcountll(y);
    });
    FORE (x, ref) {
        bool ok = false;
        FOR (i, MAX) if (dp[i + 1][x + ZERO]) {
            ok = true;
            break;
        }
        if (ok) {
            ans = __builtin_popcountll(x);
            break;
        }
    }
    cout << ans << '\n';

    return 0;
}