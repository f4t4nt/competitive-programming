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

ll mem[101][101][2][2] = {0};

void eval(ll i, ll j, str &s) {
    for (ll l = j; l >= i; l--) {
        for (ll r = l; r <= j; r++) {
            FOR (c1, 2) {
                FOR (c2, 2) {
                    if (l == r) mem[l][r][c1][c2] = 0;
                    elif (l + 1 == r) {
                        ch x = s[l], y = s[r];
                        if (c1) x ^= ('B' ^ 'W');
                        if (c2) y ^= ('B' ^ 'W');
                        mem[l][r][c1][c2] = (x == y ? 0 : 1);
                    } else {
                        set<ll> seen;
                        for (ll m = l; m < r; m++) {
                            char prv = s[m], nxt = s[m + 1];
                            if (m == l && c1) prv ^= ('B' ^ 'W');
                            if (m + 1 == r && c2) nxt ^= ('B' ^ 'W');
                            if (prv != nxt) {
                                ll lo_xr = (m == l ? 0 : mem[l][m - 1][c1][0]);
                                ll hi_xr = mem[m + 1][r][1][c2];
                                seen.insert(lo_xr ^ hi_xr);
                            }
                        }
                        for (ll m = l + 1; m <= r; m++) {
                            ch prv = s[m], nxt = s[m - 1];
                            if (m == r && c2) prv ^= ('B' ^ 'W');
                            if (m - 1 == l && c1) nxt ^= ('B' ^ 'W');
                            if (prv != nxt) {
                                ll lo_xr = mem[l][m - 1][c1][1];
                                ll hi_xr = (m == r ? 0 : mem[m + 1][r][0][c2]);
                                seen.insert(lo_xr ^ hi_xr);
                            }
                        }
                        while (seen.count(mem[l][r][c1][c2]))
                            mem[l][r][c1][c2]++;
                    }
                }
            }
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(mem, 0, sizeof(mem));    

    ll n, xr = 0; cin >> n;
    str s; cin >> s;
    FOR (i, n) {
        if (s[i] != '.') {
            ll j = i;
            while (j < n && s[j] != '.') j++;
            j--;
            eval(i, j, s);
            xr ^= mem[i][j][0][0];
            i = j;
        }
    }
    vector<pair<ll, ll>> rv;
    FOR (i, n - 1) {
        if (s[i] != '.' && s[i + 1] != '.' && s[i] != s[i + 1]) {
            ll lo = i, hi = i;
            while (lo >= 0 && s[lo] != '.') lo--;
            lo++;
            while (hi < n && s[hi] != '.') hi++;
            hi--;
            ll new_xr = xr ^ mem[lo][hi][0][0], 
                lo_xr = mem[lo][i - 1][0][0],
                hi_xr = mem[i + 1][hi][1][0];
            new_xr ^= (lo_xr ^ hi_xr);
            if (new_xr == 0) rv.pb({i, i + 1});
        }
    }
    FOB (i, 1, n) {
        if (s[i] != '.' && s[i - 1] != '.' && s[i] != s[i - 1]) {
            ll lo = i, hi = i;
            while (lo >= 0 && s[lo] != '.') lo--;
            lo++;
            while (hi < n && s[hi] != '.') hi++;
            hi--;
            ll new_xr = xr ^ mem[lo][hi][0][0],
                lo_xr = mem[lo][i - 1][0][1],
                hi_xr = mem[i + 1][hi][0][0];
            new_xr ^= lo_xr ^ hi_xr;
            if (new_xr == 0) rv.pb({i, i - 1});
        }
    }
    ssort(rv);
    cout << sz(rv) << '\n';
    for (auto [a, b] : rv) cout << a + 1 << ' ' << b + 1 << '\n';

    return 0;
}