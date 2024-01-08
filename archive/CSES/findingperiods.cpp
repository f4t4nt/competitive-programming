#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

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

constexpr ll MOD = 1e9 + 7;

bool valid(ll &len, ll &n, vector<ll> &pows, vector<ll> &hash, ll &alpha) {
    ll cur = 0;
    for (ll i = len; i <= n; i += len) {
        cur *= pows[len];
        cur %= MOD;
        cur += hash[len];
        cur %= MOD;
        if (hash[i] != cur) return false;
    }
    cur *= pows[n % len];
    cur %= MOD;
    cur += hash[n % len];
    cur %= MOD;
    return cur == hash[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    str s;
    cin >> s;
    ll n = sz(s), alpha = 26;
    vector<ll> pows(n + 1), hash(n + 1);
    pows[0] = 1;
    FOR (i, n) {
        pows[i + 1] = pows[i] * alpha % MOD;
        hash[i + 1] = (hash[i] * alpha + s[i] - 'a' + 1) % MOD;
    }
    ll len = 0;
    set<ll> rv;
    while (len++ < n) {
        if (valid(len, n, pows, hash, alpha)) {
            ll i = len;
            for (; i < n; i += len) {
                rv.insert(i);
            }
            i -= len - 1;
            for (; i <= n; i++) {
                if (valid(i, n, pows, hash, alpha)) {
                    rv.insert(i);
                }
            }
            break;
        }
    }
    rv.insert(n);
    FORE (i, rv) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}