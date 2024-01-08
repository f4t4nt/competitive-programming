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
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

ll h[6], t[2];

bool ok() {
    if (h[0] + h[1] + h[2] != t[0]) return false;
    if (h[3] + h[4] + h[5] != t[1]) return false;
    if (h[0] < h[1] || h[1] < h[2]) return false;
    if (h[3] < h[4] || h[4] < h[5]) return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(h, 0, sizeof h);
    memset(t, 0, sizeof t);

    FOR(i, 6) cin >> h[i];
    FOR(i, 2) cin >> t[i];
    sort(h, h + 6);
    do {
        if (ok()) {
            FOR(i, 6) cout << h[i] << ' ';
            cout << '\n';
            return 0;
        }
    } while(next_permutation(h, h + 6));

    return 0;
}