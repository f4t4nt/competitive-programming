#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define ins insert
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

// https://open.kattis.com/problems/permutationcfg

ll helper(ll &height, ll &val, ll &x) {
    if (val < x) {
        return 0;
    } elif (height == 0) {
        if (val == x) {
            return 1;
        } else {
            return 0;
        }
    } elif (height == 1) {
        return 1;
    } elif (height == 2) {
        return val - x + 1;
    } elif (height == 3) {
        return (val - x + 1) * (val - x + 2) / 2;
    } elif (height == 4) {
        return (val - x + 1) * (val - x + 2) * (val - x + 3) / 6;
    } else {
        return (val - x + 1) * (val - x + 2) * (val - x + 3) * (val - x + 4) / 24;
    }
    assert(false);
    return 0;
}

struct Node {
    ll val, height, lo, hi;
    vector<Node*> children;
    Node(ll val, ll height, ll lo, ll hi) : val(val), height(height), lo(lo), hi(hi) {}
    ll query(ll x, ll l, ll r, vector<ll> &p, vector<vector<ll>> &ref) {
        if (r < lo || l > hi || x > val) {
            return 0;
        }
        if (l <= lo && r >= hi) {
            return helper(height, val, x);
        }
        if (children.empty()) {
            ll lo_c = lo;
            FOR (i, sz(p)) {
                if (p[i] > val) {
                    continue;
                }
                ll hi_c = lo_c + ref[height - 1][p[i]];
                children.pb(new Node(p[i], height - 1, lo_c, hi_c - 1));
                lo_c = hi_c;
            }
        }
        ll rv = 0;
        FORE (child, children) {
            rv += child->query(x, l, r, p, ref);
        }
        return rv;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, s, q;
    cin >> n >> s >> q;
    vector<ll> p(n);
    FOR (i, n) {
        cin >> p[i];
    }

    vector<vector<ll>> ref(s + 1, vector<ll>(n + 1, 1));
    FOB (i, 1, s + 1) {
        FOB (j, 1, n + 1) {
            ref[i][j] = ref[i - 1][j] * (j + i - 1) / i;
        }
    }
    
    Node root(n, s, 1, ref[s][n]);
    FOR (i, q) {
        ll x, r;
        cin >> x >> r;
        cout << root.query(x, 1, r, p, ref) << '\n';
    }

    return 0;
}