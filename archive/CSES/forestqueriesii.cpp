#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x != e; x++)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct BIT {
    vector<ll> tree;
    ll n;
    BIT(ll n) : n(n) {
        tree.resize(n + 1);
    }
    void update(ll idx, ll val) {
        idx++;
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }
    ll query(ll idx) {
        idx++;
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
    ll query(ll l, ll r) {
        return query(r) - query(l - 1);
    }
};

struct BIT2d {
    vector<BIT> tree;
    ll n, m;
    BIT2d(ll n, ll m) : n(n), m(m) {
        tree.resize(n + 1, BIT(m));
    }
    void update(ll x, ll y, ll val) {
        x++;
        while (x <= n) {
            tree[x].update(y, val);
            x += x & (-x);
        }
    }
    ll query(ll x, ll y) {
        x++;
        ll sum = 0;
        while (x > 0) {
            sum += tree[x].query(y);
            x -= x & (-x);
        }
        return sum;
    }
    ll query(ll x1, ll y1, ll x2, ll y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    vector<str> grid(n);
    FOR (i, n) {
        cin >> grid[i];
    }
    BIT2d bit(n, n);
    FOR (i, n) {
        FOR (j, n) {
            if (grid[i][j] == '*') {
                bit.update(i, j, 1);
            }
        }
    }
    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll x, y;
            cin >> x >> y;
            x--, y--;
            if (grid[x][y] == '.') {
                grid[x][y] = '*';
                bit.update(x, y, 1);
            } else {
                grid[x][y] = '.';
                bit.update(x, y, -1);
            }
        } else {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--, y1--, x2--, y2--;
            cout << bit.query(x1, y1, x2, y2) << '\n';
        }
    }

    return 0;
}