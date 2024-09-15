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

ll MOD, inv33, res = 0;
vector<ll> hashes;

ll poww(ll a, ll b) {
    ll rv = 1;
    while (b) {
        if (b & 1) rv = rv * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return rv;
}

void compute_hashes(ll n, ll res) {
    if (n == 0) hashes[res]++;
    else FOR (x, 26) compute_hashes(n - 1, ((res * 33) ^ (x + 1)) % MOD);
}

void reduce_hash(ll n, ll target) {
    if (n == 0) res += hashes[target];
    else FOR (x, 26) reduce_hash(n - 1, ((target ^ (x + 1)) * inv33) % MOD);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k, m; cin >> n >> k >> m;
    MOD = 1 << m;
    hashes.resize(MOD);
    inv33 = poww(33, MOD / 2 - 1);
    compute_hashes((n + 1) / 2, 0);
    reduce_hash(n / 2, k);
    cout << res << '\n';

    return 0;
}