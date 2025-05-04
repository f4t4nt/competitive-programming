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
#define f first
#define s second

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> p(n), c(n), q(n);
        map<ll, ll> ranges;
        for (ll i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
            q[p[i]] = i;
        }
        for (ll &ci : c) {
            cin >> ci;
            ci--;
        }
        {
            ll i = 0, j = 0;
            while (i < n) {
                while (j < n && c[j] == c[i]) j++;
                ranges[i] = j - i;
                i = j;
            }
        }
        ll ans = 1;
        for (ll pi = 0; pi < n; pi++) {
            ll i = q[pi];
            auto it = ranges.upper_bound(i);
            assert(it != ranges.begin());
            it--;
            ans = (ans * it->s) % MOD;
            it->s--;
            if (it->s == 0) {
                auto nxt = next(it);
                ranges.erase(it);
                if (nxt != ranges.end() && nxt != ranges.begin()) {
                    auto prv = prev(nxt);
                    if (c[prv->f] == c[nxt->f]) {
                        ranges[prv->f] += nxt->s;
                        ranges.erase(nxt);
                    }
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}