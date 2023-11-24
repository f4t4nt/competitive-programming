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

ll store(ll idx, ll num, vector<bool> &mem) {
    if (num > sz(mem)) {
        return -1;
    }
    ll i = idx, j = idx, cnt = 0, len = 0;
    while (len < num) {
        cnt += mem[j];
        j = (j + 1) % sz(mem);
        len++;
    }
    do {
        if (cnt == 0) {
            ll rv = i;
            while (len--) {
                mem[i] = true;
                i = (i + 1) % sz(mem);
            }
            return rv;
        }
        cnt -= mem[i];
        i = (i + 1) % sz(mem);
        cnt += mem[j];
        j = (j + 1) % sz(mem);
    } while (i != idx);
    return -1;
}

ll free_(ll idx, ll num, vector<bool> &mem) {
    ll i = idx, cnt = 0;
    while (cnt < num) {
        assert(mem[i]);
        mem[i] = false;
        i = (i + 1) % sz(mem);
    }
    return num;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<bool> mem(m);
    vector<vector<str>> ops(n, vector<str>(3));
    FOR (i, n) {
        FOR (j, 3) {
            cin >> ops[i][j];
        }
    }
    vector<ll> rv;
    FOR (i, n) {
        if (ops[i][0] == "store") {
            rv.pb(store(stoll(ops[i][1]), stoll(ops[i][2]), mem));
        } else {
            rv.pb(free_(stoll(ops[i][1]), stoll(ops[i][2]), mem));
        }
    }
    FORE (x, rv) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}