#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll WORD = 256;
const ll MAX_M = (3000 + WORD - 1) / WORD;
static bitset<WORD> words[26][3000][MAX_M];
static vector<ll> pos[3000][26];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k; cin >> n >> k;
    vector<str> grid(n);
    ll m = (n + WORD - 1) / WORD;
    for (ll i = 0; i < n; i++) {
        cin >> grid[i];
        for (ll j = 0; j < n; j++) {
            ll c = grid[i][j] - 'A',
                idx = j / WORD,
                bit = j % WORD;
            words[c][i][idx][bit] = 1;
            pos[i][c].pb(j);
        }
    }
    ll threshold = 2e5;
    for (ll c = 0; c < k; c++) {
        ll tot = 0;
        vector<ll> heavy;
        heavy.reserve(n);
        for (ll i = 0; i < n; i++) {
            ll sz = sz(pos[i][c]);
            if (sz >= 2) heavy.pb(i);
            tot += (sz * (sz - 1)) / 2;
        }
        bool ok = false;
        if (tot < threshold) {
            set<pll> pairs;
            for (ll i = 0; i < sz(heavy) && !ok; i++) {
                for (ll j = 0; j < sz(pos[heavy[i]][c]) && !ok; j++) {
                    for (ll k = j + 1; k < sz(pos[heavy[i]][c]) && !ok; k++) {
                        ll prev_sz = sz(pairs);
                        pairs.insert({pos[heavy[i]][c][j], pos[heavy[i]][c][k]});
                        if (sz(pairs) == prev_sz) ok = true;
                    }
                }
            }
        } else {
            for (ll i = 0; i < sz(heavy) && !ok; i++) {
                for (ll j = i + 1; j < sz(heavy) && !ok; j++) {
                    ll cnt = 0;
                    for (ll idx = 0; idx < m && !ok; idx++) {
                        auto combined = words[c][heavy[i]][idx] & words[c][heavy[j]][idx];
                        cnt += combined.count();
                        if (cnt >= 2) {
                            ok = true;
                            break;
                        }
                    }
                }
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}
