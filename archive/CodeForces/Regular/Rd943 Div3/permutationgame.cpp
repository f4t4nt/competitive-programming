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

ll eval(vector<ll> &a, vector<ll> &p, ll p0, ll n, ll k) {
    ll ans = 0, sum = 0;
    vector<bool> vis(n);
    FOR (i, k) {
        if (vis[p0]) break;
        vis[p0] = 1;
        ans = max(ans, sum + (k - i) * a[p0]);
        sum += a[p0];
        p0 = p[p0];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, k, pb, ps; cin >> n >> k >> pb >> ps;
        pb--, ps--;
        vector<ll> p(n), a(n);
        FOR (i, n) {
            cin >> p[i];
            p[i]--;
        }
        FOR (i, n) cin >> a[i];
        ll bodya = eval(a, p, pb, n, k),
            sasha = eval(a, p, ps, n, k);
        if (bodya > sasha) cout << "Bodya\n";
        elif (bodya < sasha) cout << "Sasha\n";
        else cout << "Draw\n";
    }

    return 0;
}