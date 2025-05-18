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

ll eval(vector<vector<ll>> grid) {
    ll ans = 0;
    for (ll i = 0; i < sz(grid); i++) {
        for (ll j = 0; j < sz(grid); j++) {
            for (ll k = i; k < sz(grid); k++) {
                for (ll l = j; l < sz(grid); l++) {
                    set<ll> s;
                    for (ll x = i; x <= k; x++) {
                        for (ll y = j; y <= l; y++) {
                            s.insert(grid[x][y]);
                        }
                    }
                    ll mex = 0;
                    while (s.count(mex)) {
                        mex++;
                    }
                    ans += mex;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<vector<ll>> grid(n, vector<ll>(n, -1));
        ll r1 = (n - 1) / 2, r2 = r1,
            c1 = r1, c2 = r1, cur = 0;
        grid[r1][c1] = cur++;
        while (cur < n * n) {
            if (c2 + 1 < n) {
                c2++;
                for (ll r = r1; r <= r2; ++r)
                    grid[r][c2] = cur++;
            }
            if (r2 + 1 < n) {
                r2++;
                for (ll c = c2; c >= c1; --c)
                    grid[r2][c] = cur++;
            }
            if (c1 - 1 >= 0) {
                c1--;
                for (ll r = r2; r >= r1; --r)
                    grid[r][c1] = cur++;
            }
            if (r1 - 1 >= 0) {
                r1--;
                for (ll c = c1; c <= c2; ++c)
                    grid[r1][c] = cur++;
            }
        }
        for (auto &row : grid) {
            for (ll x : row) {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}
