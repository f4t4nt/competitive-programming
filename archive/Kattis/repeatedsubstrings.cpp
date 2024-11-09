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
    ll,
    null_type,
    less<ll>,
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
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
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

struct SuffixArray {
    ll n; str s;
    vector<ll> sa, lcp;

    SuffixArray(str &s) : n(sz(s) + 1), s(s + '$'), sa(n - 1), lcp(n - 1) {
        vector<pair<pll, ll>> suffs(n);
        FOR (i, n) suffs[i] = { { s[i], s[i] }, i };
        ssort(suffs);
        vector<ll> equiv(n);
        FOR1 (i, n) {
            auto [c_val, cs] = suffs[i];
            auto [p_val, ps] = suffs[i - 1];
            equiv[cs] = equiv[ps] + (c_val > p_val);
        }
        for (ll idx = 1; idx < n; idx *= 2) {
            for (auto &[val, s] : suffs)
                val = { equiv[s], equiv[(s + idx) % n] };
            radix_sort(suffs);
            FOR (i, n - 1) {
                auto [p_val, ps] = suffs[i];
                auto [c_val, cs] = suffs[i + 1];
                equiv[cs] = equiv[ps] + (c_val > p_val);
            }
        }
        // --- for lcp ---
        vector<ll> idxs(n);
        FOR (i, n) idxs[suffs[i].s] = i;
        ll start_at = 0;
        FOR (i, n - 1) {
            ll prv = suffs[idxs[i] - 1].s,
                cur = start_at;
            while (s[i + cur] == s[prv + cur]) cur++;
            lcp[idxs[i] - 1] = cur;
            start_at = max(0LL, cur - 1);
        }
        // ---------------
        n--; // account for $
        this->s.pop_back();
        FOR (i, n) sa[i] = suffs[i + 1].s;
    }

    void radix_sort(vector<pair<pll, ll>> &arr) {
        for (ll i : {2, 1}) {
            auto key = [&](const pair<pll, ll> &x) {
                return i == 1 ? x.f.f : x.f.s;
            };
            ll mx = 0;
            for (auto &i : arr) mx = max(mx, key(i));
            vector<ll> occs(mx + 1);
            for (auto &i : arr) occs[key(i)]++;
            vector<ll> start(mx + 1);
            FOR (i, mx) start[i + 1] = start[i] + occs[i];
            vector<pair<pll, ll>> new_arr(n);
            for (auto &i : arr) new_arr[start[key(i)]++] = i;
            arr = new_arr;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        str s; cin >> s;
        SuffixArray sa(s);
        ll n = sz(s);
        ll ans = 0;
        FOR (i, n - 1) ans += max(0LL, sa.lcp[i + 1] - sa.lcp[i]);
        cout << ans << '\n';
    }

    return 0;
}