#include <bits/stdc++.h>
using namespace std;

#define all(C) C.begin(), C.end()
#define sz(C) (ll) C.size()

typedef long long ll;

struct DSU {
    ll        cnt;  // current number of connected components
    vector<ll> e;   // parent / (-size) array
                    //  -e[v] = size of component if v is root
                    //   e[v] = parent of v otherwise

    DSU(ll n = 0) { init(n); }

    // create n single-element sets
    void init(ll n) {
        cnt = n;
        e.assign(n, -1);
    }

    // make all elements singleton
    void reset() {
        fill(all(e), -1);
        cnt = sz(e);
    }

    // find + compress
    ll get(ll x) {
        return e[x] < 0 ? x : e[x] = get(e[x]);
    }

    // union by size; true if merged
    bool unite(ll a, ll b) {
        a = get(a);  b = get(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b); // ensure |a| >= |b|
        e[a] += e[b];
        e[b]  = a;
        --cnt;
        return true;
    }

    // queries
    bool same_set(ll a, ll b) { return get(a) == get(b); }
    ll size      (ll x)       { return -e[get(x)]; }
};
