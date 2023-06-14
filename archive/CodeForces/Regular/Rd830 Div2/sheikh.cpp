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

ll get_f(ll l, ll r, vector<ll> &sum, vector<ll> &xor_) {
    return (sum[r] - sum[l - 1]) - (xor_[r] ^ xor_[l - 1]);
}

pair<ll, ll> get_l_r(ll &bound_l, ll &bound_r, vector<ll> &sum, vector<ll> &xor_, vector<ll> &nonzero, ll &f, ll &len) {
    ll idx = lower_bound(nonzero.begin(), nonzero.end(), bound_l) - nonzero.begin();
    ll l = nonzero[idx], r = l + len - 1, cnt = 0;
    while (idx < sz(nonzero) && r <= bound_r && cnt < 32) {
        ll f_ = get_f(l, r, sum, xor_);
        if (f_ == f) {
            return mp(l, r);
        }
        idx++;
        l = nonzero[idx];
        r = l + len - 1;
        cnt++;
    }
    idx = upper_bound(nonzero.begin(), nonzero.end(), bound_r) - nonzero.begin() - 1;
    r = nonzero[idx], l = r - len + 1, cnt = 0;
    while (idx >= 0 && l >= bound_l && cnt < 32) {
        ll f_ = get_f(l, r, sum, xor_);
        if (f_ == f) {
            return mp(l, r);
        }
        idx--;
        r = nonzero[idx];
        l = r - len + 1;
        cnt++;
    }
    return mp(-1, -1);
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, q;
        cin >> n >> q;
        vector<ll> a(n + 1), sum(n + 1), xor_(n + 1), nonzero;
        FOB(i, 1, n + 1) {
            cin >> a[i];
            sum[i] = sum[i - 1] + a[i];
            xor_[i] = xor_[i - 1] ^ a[i];
            if (a[i] != 0) {
                nonzero.pb(i);
            }
        }
        FOR(i, q) {
            ll bound_l, bound_r;
            cin >> bound_l >> bound_r;
            ll f = get_f(bound_l, bound_r, sum, xor_);
            if (f == 0) {
                cout << bound_l << ' ' << bound_l << '\n';
                continue;
            }
            ll lo = 1, hi = bound_r - bound_l + 1;
            // find smallest len such that get_l_r returns a valid pair
            while (lo < hi) {
                ll mid = (lo + hi) / 2;
                pair<ll, ll> p = get_l_r(bound_l, bound_r, sum, xor_, nonzero, f, mid);
                if (p.first == -1) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            pair<ll, ll> p = get_l_r(bound_l, bound_r, sum, xor_, nonzero, f, lo);
            cout << p.first << ' ' << p.second << '\n';
        }
    }
    return 0;
}