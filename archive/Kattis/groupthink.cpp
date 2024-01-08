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

bool associativity(ll &n, vector<vector<ll>> &table) {
    FOR (x, n) {
        FOR (y, n) {
            FOR (z, n) {
                if (table[table[x][y]][z] != table[x][table[y][z]]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool identity(ll &n, vector<vector<ll>> &table, vector<ll> &ids) {
    FOR (x, n) {
        bool ok = true;
        FOR (y, n) {
            if (table[x][y] != y || table[y][x] != y) {
                ok = false;
                break;
            }
        }
        if (ok) {
            ids.pb(x);
        }
    }
    return sz(ids);
}

bool inverses(ll &n, vector<vector<ll>> &table, vector<ll> &ids) {
    FORE (id, ids) {
        bool id_ok = true;
        FOR (x, n) {
            bool ok = false;
            FOR (y, n) {
                if (table[x][y] == id && table[y][x] == id) {
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                id_ok = false;
                break;
            }
        }
        if (id_ok) {
            return true;
        }
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<vector<ll>> table(n, vector<ll>(n));
    FOR (i, n * n) {
        ll a, b, c;
        cin >> a >> b >> c;
        table[a][b] = c;
    }
    vector<ll> ids;
    vector<bool> ps = {
        associativity(n, table),
        identity(n, table, ids),
        inverses(n, table, ids)
    };
    if (ps[0] && ps[1] && ps[2]) {
        cout << "group\n";
    } elif (ps[0] && ps[1]) {
        cout << "monoid\n";
    } elif (ps[0]) {
        cout << "semigroup\n";
    } else {
        cout << "magma\n";
    }

    return 0;
}