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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll ALPH = 26;
const ll MOD = 1e15 + 7;

bool ok(str &s, ll mid, ll n, ll k) {
    ll hash = 0, cnt = 1;
    FOR (i, mid) {
        hash *= ALPH;
        hash += s[i] - 'a' + 1;
        hash %= MOD;
    }
    ll pop_pow = 1;
    FOR (i, mid) {
        pop_pow *= ALPH;
        pop_pow %= MOD;
    }
    ll start = mid;
    while (cnt < k && start < n - mid + 1) {
        ll cur_hash = 0;
        FOR (i, mid) {
            cur_hash *= ALPH;
            cur_hash += s[start + i] - 'a' + 1;
            cur_hash %= MOD;
        }
        ll lo_idx = start, hi_idx = start + mid;
        while (hi_idx <= n) {
            if (cur_hash == hash) {
                cnt++;
                break;
            }
            cur_hash *= ALPH;
            cur_hash += s[hi_idx] - 'a' + 1;
            cur_hash %= MOD;
            cur_hash -= (s[lo_idx] - 'a' + 1) * pop_pow;
            cur_hash %= MOD;
            cur_hash += MOD;
            cur_hash %= MOD;
            lo_idx++;
            hi_idx++;
        }
        start = hi_idx;
    }
    return cnt == k;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, l, r; cin >> n >> l >> r;
        str s; cin >> s;
        n = sz(s);
        ll lo = 0, hi = sz(s);
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            if (ok(s, mid, n, l)) lo = mid;
            else hi = mid - 1;
        }
        cout << lo << '\n';
    }

    return 0;
}