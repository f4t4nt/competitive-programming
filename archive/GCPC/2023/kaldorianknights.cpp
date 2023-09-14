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

constexpr ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, h;
    cin >> n >> h;
    vector<ll> fac(n + 1);
    fac[0] = 1;
    FOB (i, 1, n + 1) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    vector<ll> k(h + 2);
    FOB (i, 1, h + 1) {
        cin >> k[i];
        k[i] += k[i - 1];
    }
    k[h + 1] = n;
    vector<ll> cnt(h + 2);
    FOB (i, 1, h + 2) {
        cnt[i] = fac[k[i]];
        FOB (j, 1, i) {
            cnt[i] = (cnt[i] - cnt[j] * fac[k[i] - k[j]] % MOD + MOD) % MOD;
        }
    }
    cout << cnt[h + 1] << '\n';

    return 0;
}