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
// #define x first
// #define y second

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    // ll t = 720;
    // cout << t << '\n';
    // vector<ll> tmp(6);
    // iota(all(tmp), 1);
    // while (t--) {
    //     ll n = 6, q = 100;
    //     next_permutation(all(tmp));
    //     cout << n << ' ' << q << '\n';
    //     for (ll x : tmp) cout << x << ' ';
    //     cout << '\n';
    //     cout << "R";
    //     FOR (i, n - 2) cout << (rng() % 2 ? 'L' : 'R');
    //     cout << "L";
    //     cout << '\n';
    //     while (q--) cout << rng() % (n - 2) + 2 << ' ';
    //     cout << '\n';
    // }
    // return 0;

    ll lines = 1;
    ll t; cin >> t;
    while (t--) {
        ll n, q; cin >> n >> q;
        vector<ll> a(n);
        FOR (i, n) cin >> a[i];
        str s; cin >> s;
        ll cnt = 0;
        set<ll> cur_cuts, good_cuts;
        ll lo = 1, hi = -1;
        vector<bool> found(n + 1);
        FOR (i, n) {
            hi = max(hi, a[i]);
            found[a[i]] = true;
            while (lo <= hi && found[lo]) lo++;
            if (lo > hi) good_cuts.insert(i);
        }
        FOR (i, n - 1) if (s[i] == 'L' && s[i + 1] == 'R') {
            cur_cuts.insert(i);
            if (!good_cuts.count(i)) cnt++;
        }
        while (q--) {
            ll i; cin >> i;
            i--;
            if (s[i] == 'L' && s[i + 1] == 'R') {
                cur_cuts.erase(i);
                if (!good_cuts.count(i)) cnt--;
            }
            if (s[i] == 'R' && s[i - 1] == 'L') {
                cur_cuts.erase(i - 1);
                if (!good_cuts.count(i - 1)) cnt--;
            }
            s[i] = 'R' + 'L' - s[i];
            if (s[i] == 'L' && s[i + 1] == 'R') {
                cur_cuts.insert(i);
                if (!good_cuts.count(i)) cnt++;
            }
            if (s[i] == 'R' && s[i - 1] == 'L') {
                cur_cuts.insert(i - 1);
                if (!good_cuts.count(i - 1)) cnt++;
            }
            cout << (cnt == 0 ? "YES" : "NO") << '\n';
            lines++;
        }
    }

    return 0;
}