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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll)C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<ll> a(n * m + 1), b = a;
        for (ll i = 1; i <= n * m; i++) cin >> a[i];
        for (ll i = 1; i <= n * m; i++) cin >> b[i];
        vector<ll> apos(2 * n * m + 1, -1), bpos = apos;
        for (ll i = 1; i <= n * m; i++) bpos[b[i]] = i;
        for (ll i = 1; i <= n * m; i++) {
            if (bpos[a[i]] == -1) break;
            apos[i] = bpos[a[i]];
        }
        apos[0] = 0;
        ll skip = 0, pre = 0;
        bool prv = true;
        for (ll i = 1; i <= n * m; i++) {
            if (apos[i - 1] > apos[i]) break;
            ll d = apos[i] - apos[i - 1] - 1;
            if (prv) skip += d;
            elif (d > 0) break;
            if ((i + skip) / m > (i - 1) / m) prv = true;
            else prv = false;
            if (prv) pre = i;
        }
        cout << n * m - pre << '\n';
    }

    return 0;
}