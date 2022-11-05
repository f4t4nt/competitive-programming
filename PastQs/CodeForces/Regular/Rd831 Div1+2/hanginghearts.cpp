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

ll longest_non_decreasing_subsequence(vector<ll> p) {
    multiset<ll> s;
    FORE(x, p) {
        auto it = s.upper_bound(x);
        if (it != s.end()) {
            s.erase(it);
        }
        s.insert(x);
    }
    return sz(s);
}
 
ll dfs(ll i, ll &x, vector<ll> &seq, vector<vector<ll>> &c) {
    if (sz(c[i]) == 0) {
        seq.pb(x);
        x++;
        return x;
    } else {
        ll m = x;
        FORE (j, c[i]) {
            m = min(m, dfs(j, x, seq, c));
        }
        seq.pb(m);
        return m;
    }
}
 
ll find_tree_size(ll i, vector<vector<ll>> &c, vector<ll> &tree_size) {
    ll s = 0;
    FORE (j, c[i]) {
        s += find_tree_size(j, c, tree_size);
    }
    tree_size[i] = s + 1;
    return s + 1;
}

ll find_tree_depth(ll i, vector<vector<ll>> &c, vector<ll> &tree_depth) {
    ll d = 0;
    FORE (j, c[i]) {
        d = max(d, find_tree_depth(j, c, tree_depth));
    }
    tree_depth[i] = d + 1;
    return d + 1;
}

int main() {
    ll n, x = 1;
    cin >> n;
    vector<ll> p(n), seq, tree_size(n), tree_depth(n);
    vector<vector<ll>> c(n);
    p[0] = 0;
    FOB (i, 1, n) {
        cin >> p[i];
        p[i]--;
        c[p[i]].pb(i);
    }
    // find_tree_size(0, c, tree_size);
    // FORE (v, c) {
    //     sort(v.begin(), v.end(), [&tree_size](ll i, ll j) {
    //         return tree_size[i] > tree_size[j];
    //     });
    // }
    find_tree_depth(0, c, tree_depth);
    FORE (v, c) {
        sort(v.begin(), v.end(), [&tree_depth](ll i, ll j) {
            return tree_depth[i] > tree_depth[j];
        });
    }
    dfs(0, x, seq, c);
    cout << longest_non_decreasing_subsequence(seq) << '\n';
    return 0;
}