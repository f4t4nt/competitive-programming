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

const ll MOD = 998244353;

ll eval(ll n, bitset<300000> &xors) {
    ll cnt[2] = {1, 0}, sum[2] = {0, 0}, rv = 0, cur = 0;
    FOR (i, n) {
        cur ^= xors[i];
        cnt[cur]++;
        sum[cur] += i + 1;
        rv = (rv + cnt[cur ^ 1] * (i + 1) - sum[cur ^ 1]) % MOD;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    bitset<300000> bits;
    ll n, rv = 0;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) cin >> a[i];
    FOR (i, 30) {
        FOR (j, n) {
            bits[j] = (a[j] >> i) & 1;
        }
        ll tmp = eval(n, bits);
        rv = (rv + (1 << i) * tmp) % MOD;
    }
    cout << rv << '\n';

    return 0;
}