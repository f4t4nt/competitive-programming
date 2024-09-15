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
// #define f first
// #define s second

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

bool check(ll n, ll k, vector<ll> a) {
    bitset<1000001> b;
    b[0] = 1;
    FORE (x, a) b |= b << x;
    bool ok = 1;
    FOR (i, n + 1) {
        if (i == k) ok &= !b[i];
        else ok &= b[i];
    }
    return ok;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        vector<ll> ans;
        FOR (i, 21) ans.pb(1LL << i);
        ans.pb(k + 1);
        ll sum = 0, idx = 0;
        while (sum < k) sum += ans[idx++];
        sum -= ans[--idx];
        ans.pb(3 * ans[idx]);
        ans[idx] = k - sum - 1;
        // assert(check(n, k, ans));
        if (!check(n, k, ans)) while (true) continue;
        cout << sz(ans) << '\n';
        FORE (x, ans) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}