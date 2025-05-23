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

bool valid(ll &i, ll &j, ll &n, vector<ll> &cnts) {
    ll rem = n - i;
    if (cnts[j] * 2 - 1 > rem) {
        return false;
    }
    ll mx = 0;
    FOR (k, 26) {
        if (k != j) {
            mx = max(mx, cnts[k]);
        }
    }
    if (2 * mx > rem) {
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    str s;
    cin >> s;
    ll n = sz(s);
    str t(n, '.');
    vector<ll> cnts(26);
    FORE (x, s) {
        cnts[x - 'A']++;
    }
    FOR (i, n) {
        bool ok = false;
        FOR (j, 26) {
            if (i > 0 && t[i - 1] == 'A' + j) {
                continue;
            }
            if (cnts[j] == 0) {
                continue;
            }
            if (valid(i, j, n, cnts)) {
                t[i] = 'A' + j;
                cnts[j]--;
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << -1 << '\n';
            return 0;
        }
    }
    cout << t << '\n';

    return 0;
}