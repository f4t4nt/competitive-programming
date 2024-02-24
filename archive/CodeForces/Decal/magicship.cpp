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
#define x first
#define y second

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

bool valid(ll t, ll n, ll x1, ll y1, vector<pll> &conv) {
    ll rep = t / n, x = conv[n - 1].x * rep, y = conv[n - 1].y * rep;
    ll rem = t % n;
    if (rem) {
        x += conv[rem - 1].x;
        y += conv[rem - 1].y;
    }
    return abs(x - x1) + abs(y - y1) <= t;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
    x1 -= x0, y1 -= y0;
    x0 = y0 = 0;
    ll n; cin >> n;
    str s; cin >> s;
    vector<pll> conv(n);
    ll tx = 0, ty = 0;
    FOR (i, n) {
        if (s[i] == 'U') ty++;
        elif (s[i] == 'D') ty--;
        elif (s[i] == 'L') tx--;
        else tx++;
        conv[i] = {tx, ty};
    }
    ll lo = 0, hi = 1e18;
    if (!valid(hi, n, x1, y1, conv)) cout << -1 << '\n';
    else {
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (valid(mid, n, x1, y1, conv)) hi = mid;
            else lo = mid + 1;
        }
        cout << lo << '\n';
    }

    return 0;
}