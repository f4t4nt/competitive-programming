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

bool valid(str &m, ll &tx, ll &ty, ll &rx, ll &ry, str &res) {
    ll idx = 0;
    bool h = false;
    FORE (c, m) {
        if (idx == 0) {
            res[0] = 'R';
            if (c == 'N') {
                ry++;
            } elif (c == 'S') {
                ry--;
            } elif (c == 'E') {
                rx++;
            } elif (c == 'W') {
                rx--;
            }
            idx++;
            continue;
        }
        if (c == 'N') {
            // if (ry != ty / 2) {
            if (abs(ry - ty / 2) > abs(ry + 1 - ty / 2)) {
                ry++;
                res[idx++] = 'R';
            } else {
                res[idx++] = 'H';
                h = true;
            }
        } elif (c == 'S') {
            // if (ry != ty / 2) {
            if (abs(ry - ty / 2) > abs(ry - 1 - ty / 2)) {
                ry--;
                res[idx++] = 'R';
            } else {
                res[idx++] = 'H';
                h = true;
            }
        } elif (c == 'E') {
            // if (rx != tx / 2) {
            if (abs(rx - tx / 2) > abs(rx + 1 - tx / 2)) {
                rx++;
                res[idx++] = 'R';
            } else {
                res[idx++] = 'H';
                h = true;
            }
        } elif (c == 'W') {
            // if (rx != tx / 2) {
            if (abs(rx - tx / 2) > abs(rx - 1 - tx / 2)) {
                rx--;
                res[idx++] = 'R';
            } else {
                res[idx++] = 'H';
                h = true;
            }
        }
    }
    if (rx != tx / 2 || ry != ty / 2 || !h) {
        return false;
    } else {
        return true;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        str m; cin >> m;
        ll tx = 0, ty = 0;
        FORE (c, m) {
            if (c == 'N') ty++;
            elif (c == 'S') ty--;
            elif (c == 'E') tx++;
            else tx--;
        }
        if (abs(tx) % 2 == 1 || abs(ty) % 2 == 1) {
            cout << "NO\n";
        } else {
            ll rx = 0, ry = 0;
            str res(sz(m), ' ');
            if (valid(m, tx, ty, rx, ry, res)) {
                cout << res << '\n';
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}