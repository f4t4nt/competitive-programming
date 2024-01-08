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

const ll MOD = 1e6 + 3;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<str> ins(n), outs(n);
    map<str, ll> in_cnt, out_cnt;
    FOR (i, m) {
        str in, out;
        cin >> in >> out;
        FOR (j, n) {
            ins[j] += in[j];
            outs[j] += out[j];
        }
    }
    FOR (i, n) {
        in_cnt[ins[i]]++;
        out_cnt[outs[i]]++;
    }
    FORE (x, in_cnt) {
        if (out_cnt[x.first] != x.second) {
            cout << 0 << '\n';
            return 0;
        }
    }

    vector<ll> fact(n + 1, 1);
    FOR (i, n) {
        fact[i + 1] = (fact[i] * (i + 1)) % MOD;
    }
    ll rv = 1;
    FORE (x, in_cnt) {
        rv = (rv * fact[x.second]) % MOD;
    }
    cout << rv << '\n';

    return 0;
}