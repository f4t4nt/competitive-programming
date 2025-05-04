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
// #define f first
// #define s second

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
        ll n; cin >> n;
        str s; cin >> s;
        if (n == 1) {
            cout << (s == "0" ? 0 : 1) << '\n';
            continue;
        }
        vector<pll> ranges;
        {
            ll l = 0, r = 0;
            while (l < n) {
                while (l < n && s[l] == '1') l++;
                r = l;
                while (r < n && s[r] == '0') r++;
                if (l < n) {
                    ranges.pb({l, r});
                    l = r;
                }
            }
        }
        pll prv = {-1, 0};
        ll ans = 1;
        for (auto [l, r] : ranges) {
            ll top = (r - l) * (l + r - 1) / 2,
                bot = (r - l) * (n - 1) - top;
            if (l > 0) {
                if (prv.first == l - 1) top += prv.second;
                else top++;
            }
            if (r < n) {
                bot++;
                prv = {r, bot};
            }
            ans = max({ans, top, bot});
        }
        cout << ans << '\n';
    }

    return 0;
}