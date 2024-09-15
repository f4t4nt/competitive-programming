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
    pld,
    null_type,
    less<pld>,
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
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 1e9 + 7;

vector<ll> mult(vector<ll> a, vector<ll> b) {
    vector<ll> res(10, 0);
    FOR (i, 10) FOR (j, 10) {
        res[(i + j) % 10] += a[i] * b[j];
        res[(i + j) % 10] %= MOD;
    }
    return res;
}

vector<ll> binpow(vector<ll> a, ll n) {
    vector<ll> res(10, 0);
    res[0] = 1;
    while (n) {
        if (n & 1) res = mult(res, a);
        a = mult(a, a);
        n >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<ll> res(10, 0), p(10);
    res[0] = 1;
    FOR (i, 10) {
        p[i] = n / 10 + (i > 0 && n % 10 >= i);
        vector<ll> a(10, 0);
        a[0]++, a[i]++;
        a = binpow(a, p[i]);
        res = mult(res, a);
    }
    cout << res[7] << '\n';

    return 0;
}