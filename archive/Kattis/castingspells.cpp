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
// #define f first
// #define s second

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

vector<ll> manacher(str &s) {
    str t = "$#";
    for (char c : s) { t += c; t += '#'; }
    ll n = sz(t);
    ll center = 0, max_rad = -1, rad;
    vector<ll> p(n);
    FOR (i, n) {
        if (i <= max_rad) rad = min(p[2 * center - i], max_rad - i);
        else rad = 0;
        while (i - rad - 1 >= 0 && i + rad + 1 < n && t[i - rad - 1] == t[i + rad + 1]) rad++;
        p[i] = rad;
        if (i + rad > max_rad) {
            center = i;
            max_rad = i + rad;
        }
    }
    vector<ll> res;
    for (ll i = 1; i < n; i += 2) res.pb(p[i] / 2);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    str s; cin >> s;
    auto p = manacher(s);
    multiset<ll> lens;
    set<pll> active;
    ll res = 0, asdf = 0;
    FOR (i, sz(p)) {
        while (!active.empty() && active.begin()->first < i) {
            lens.erase(lens.find(active.begin()->second));
            active.erase(active.begin());
        }
        if (!lens.empty()) {
            auto it = lens.lower_bound(i - p[i]);
            if (it != lens.end()) {
                ll tmp = (i - *it);
                if (res < 4 * tmp && i + tmp < p.size() && p[i + tmp] >= tmp) {
                    res = 4 * tmp;
                    asdf = i;
                }
            }
        }
        active.insert({i + p[i], i});
        lens.insert(i);
    }
    cout << res << '\n';
    // cout << asdf << '\n';
    // cout << p[asdf] << '\n';
    // cout << s.substr(asdf - p[asdf], 2 * p[asdf]) << '\n';
    // cout << s.substr(asdf - res / 2, res) << '\n';

    return 0;
}