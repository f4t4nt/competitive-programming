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
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n; cin >> n;
    vector<ll> h(n), dec(n + 1), inc(n + 1);
    FOR (i, n) cin >> h[i];
    FOR (i, n) {
        if (h[i + 1] >= h[i]) inc[i + 1] = inc[i];
        else inc[i + 1] = i + 1;
    }
    dec[n] = n - 1;
    FORR (i, n) {
        if (h[i + 1] <= h[i]) dec[i] = dec[i + 1];
        else dec[i] = i;
    }
    ll rv = 0;
    FOR (i, n) {
        ll l = dec[i + 1], r = inc[i];
        rv = max(rv, h[i] - max(h[l], h[r]));
    }
    cout << rv << '\n';

    return 0;
}