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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll CNT;

bool dfs(vector<ll> &a, vector<ll> &nxt0, vector<ll> &rem, ll i, ll n, ll m, ll cnt0, ll sum = 0, ll prod = -1) {
    if (CNT-- <= 0) return false;
    if (sum + rem[i + 1] > m) return false;
    if (sum > m) return false;
    if (sum + prod > m) {
        if (cnt0 == 0) return false;
        if (dfs(a, nxt0, rem, nxt0[i] + 1, n, m, cnt0 - 1, sum, 0)) return true;
    }
    if (sum + prod == m && cnt0 > 0) return true;
    if (i == n) return (sum + prod) == m;
    cnt0 -= a[i] == 0;
    if (prod == -1) {
        if (dfs(a, nxt0, rem, i + 1, n, m, cnt0, sum, a[i])) return true;
    } else {
        if (1) {
            if (dfs(a, nxt0, rem, i + 1, n, m, cnt0, sum + prod, a[i])) return true;
            if (dfs(a, nxt0, rem, i + 1, n, m, cnt0, sum, prod * a[i])) return true;
        } else {
            if (dfs(a, nxt0, rem, i + 1, n, m, cnt0, sum, prod * a[i])) return true;
            if (dfs(a, nxt0, rem, i + 1, n, m, cnt0, sum + prod, a[i])) return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m, mn = 101, cnt0 = 0; cin >> n >> m;
        vector<ll> a(n), nxt0(n), rem(n, 101);
        FOR (i, n) {
            cin >> a[i];
            mn = min(mn, a[i]);
            if (a[i] == 0) cnt0++;
        }
        if (mn > m || (mn > 1 && n > 50)) {
            cout << "NO\n";
            continue;
        }
        ll j = -1;
        FORR (i, n) {
            nxt0[i] = j;
            if (a[i] == 0) j = i;
        }
        rem.back() = a.back();
        FORR (i, n - 1) {
            if (a[i] == 0 || rem[i + 1] == 0) rem[i] = 0;
            elif (a[i] == 1) rem[i] = min(rem[i], rem[i + 1]);
            else rem[i] = min(rem[i], rem[i + 1] + a[i]);
        }
        rem.pb(0);
        CNT = 1e6;
        cout << (dfs(a, nxt0, rem, 0, n, m, cnt0) ? "YES" : "NO") << '\n';
    }

    return 0;
}