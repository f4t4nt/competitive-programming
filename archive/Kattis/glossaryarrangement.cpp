#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

vector<ll> valid(ll &mid, ll &n, ll &w, vector<str> &s) {
    vector<pair<ll, ll>> dp(n);
    dp[0] = {sz(s[0]), 0};
    FOB (i, 1, n) {
        ll max_len = sz(s[i]);
        dp[i] = {dp[i - 1].first + 1 + max_len, i};
        for (ll j = i - 1; j >= max(0LL, i - mid + 1); j--) {
            max_len = max(max_len, sz(s[j]));
            ll tmp = 0;
            if (j > 0) {
                tmp = dp[j - 1].first + 1;
            }
            dp[i] = min(dp[i], {tmp + max_len, j});
        }
    }
    if (dp[n - 1].first > w) {
        return {};
    } else {
        vector<ll> rv;
        ll i = n - 1;
        while (i >= 0) {
            rv.pb(dp[i].second);
            i = dp[i].second - 1;
        }
        flip(rv);
        return rv;
    }
}

int main() {
    ll n, w;
    cin >> n >> w;
    vector<str> s(n);
    FOR (i, n) {
        cin >> s[i];
    }
    ll lo = 1, hi = n;
    vector<ll> ref;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        vector<ll> tmp = valid(mid, n, w, s);
        if (sz(tmp) > 0) {
            hi = mid;
            ref = tmp;
        } else {
            lo = mid + 1;
        }
    }
    vector<pair<ll, vector<str>>> rv;
    FOR (i, sz(ref) - 1) {
        rv.pb({0, vector<str>(s.begin() + ref[i], s.begin() + ref[i + 1])});
    }
    if (sz(ref) > 0) {
        rv.pb({0, vector<str>(s.begin() + ref[sz(ref) - 1], s.end())});
    } else {
        rv.pb({0, s});
    }
    FOR (i, sz(rv)) {
        ll max_len = 0;
        FORE (j, rv[i].second) {
            max_len = max(max_len, sz(j));
        }
        rv[i].first = max_len;
    }
    cout << lo << ' ' << sz(rv) << '\n';
    FOR (i, sz(rv)) {
        cout << rv[i].first << ' ';
    }
    cout << '\n';
    FOR (i, lo) {
        FOR (j, sz(rv)) {
            if (i < sz(rv[j].second)) {
                cout << rv[j].second[i];
                FOB (k, sz(rv[j].second[i]), rv[j].first) {
                    cout << ' ';
                }
            } else {
                FOB (k, 0, rv[j].first) {
                    cout << ' ';
                }
            }
            if (j < sz(rv) - 1) {
                cout << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}