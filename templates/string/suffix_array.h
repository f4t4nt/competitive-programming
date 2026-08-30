#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef string str;
typedef pair<ll, ll> pll;

#define all(C) C.begin(), C.end()
#define sz(C) (ll) C.size()

// -----------------------------------------------------------------------------
//  Suffix Array
// -----------------------------------------------------------------------------
//  Supports:   - sa[i]  = start index of the i-th smallest suffix of s
//              - lcp[i] = longest common prefix of suffixes sa[i] and sa[i + 1]
//  Complexity: O(n log n) build (rank doubling + radix sort), O(n) lcp (Kasai)
//  Notes:      - lcp of arbitrary suffixes sa[i], sa[j] (i < j) is
//                min(lcp[i..j-1]), use sparse table / RMQ over lcp
//              - appends '$' internally; s must not contain it
// -----------------------------------------------------------------------------
struct SuffixArray {
    ll n;             // length of s
    str s;
    vector<ll> sa;    // sa[i] = start of i-th smallest suffix
    vector<ll> lcp;   // lcp[i] = lcp(suffix sa[i], suffix sa[i + 1]), size n - 1

    SuffixArray(str &s_in) : n(sz(s_in)), s(s_in), sa(n), lcp(max(n - 1, 0LL)) {
        str t = s + '$';
        ll m = n + 1;
        // (rank pair, start); compared prefix length doubles each round
        vector<pair<pll, ll>> suffs(m);
        for (ll i = 0; i < m; i++) suffs[i] = { { t[i], t[i] }, i };
        sort(all(suffs));
        vector<ll> equiv(m);
        for (ll i = 1; i < m; i++)
            equiv[suffs[i].second] = equiv[suffs[i - 1].second] + (suffs[i].first > suffs[i - 1].first);
        for (ll len = 1; len < m; len *= 2) {
            for (auto &[val, at] : suffs) val = { equiv[at], equiv[(at + len) % m] };
            radix_sort(suffs);
            for (ll i = 1; i < m; i++)
                equiv[suffs[i].second] = equiv[suffs[i - 1].second] + (suffs[i].first > suffs[i - 1].first);
        }
        for (ll i = 0; i < n; i++) sa[i] = suffs[i + 1].second; // rank 0 is "$"

        // Kasai: suffixes left to right, lcp drops by at most 1 per step
        vector<ll> rnk(m);
        for (ll i = 0; i < m; i++) rnk[suffs[i].second] = i;
        ll cur = 0;
        for (ll i = 0; i < m - 1; i++) {
            ll prv = suffs[rnk[i] - 1].second;
            while (t[i + cur] == t[prv + cur]) cur++;
            if (rnk[i] >= 2) lcp[rnk[i] - 2] = cur; // rnk[i] == 1 compares against "$"
            cur = max(0LL, cur - 1);
        }
    }

    // stable two-pass counting sort on the rank pair
    void radix_sort(vector<pair<pll, ll>> &arr) {
        for (ll pass : {1, 0}) {
            auto key = [&](pair<pll, ll> &x) { return pass ? x.first.second : x.first.first; };
            ll mx = 0;
            for (auto &x : arr) mx = max(mx, key(x));
            vector<ll> start(mx + 2);
            for (auto &x : arr) start[key(x) + 1]++;
            for (ll i = 0; i <= mx; i++) start[i + 1] += start[i];
            vector<pair<pll, ll>> out(sz(arr));
            for (auto &x : arr) out[start[key(x)]++] = x;
            arr = out;
        }
    }
};
