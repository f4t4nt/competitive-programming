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

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

const ll MAXN = 1e5;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll k = 2 * MAXN / 3 + 2;
    cout << k << endl;
    vector<ll> idx(MAXN + 1, -1);
    FOR (i, MAXN + 1) {
        if (i % 3 == 0) idx[i] = 2 * (i / 3) + 1;
        elif (i == MAXN) idx[i] = k;
    }
    while (1) {
        ll x; cin >> x;
        if (x == -1) {
            for (ll i = 1; i < MAXN; i += 3) {
                if (idx[i] == -1 && idx[i + 1] == -1) {
                    idx[i] = 2 * (i / 3) + 2;
                }
            }
            FOR (i, MAXN + 1) {
                if (idx[i] != -1) {
                    cout << i << endl;
                }
            }
            break;
        } else {
            cout << idx[x] << endl;
            if (idx[x] == -1) {
                if (x % 3 != 0) {
                    if ((x + 1) % 3 != 0) {
                        idx[x + 1] = 2 * (x / 3) + 2;
                    } else {
                        idx[x - 1] = 2 * (x / 3) + 2;
                    }
                }
            }
        }
    }

    return 0;
}