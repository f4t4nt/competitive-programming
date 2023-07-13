#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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

void split(
    vector<ll> &s,
    ll idx,
    ll val,
    ll x,
    vector<vector<ll>> &nxt,
    ll last,
    vector<ll> &a,
    vector<ll> &nv,
    set<vector<ll>> &vis
) {
    if (idx == sz(s)) {
        if (val <= x) {
            vector<ll> nnv = nv;
            ssort(nnv);
            if (!vis.count(nnv)) {
                vis.insert(nnv);
                nxt.pb(nnv);
            }
        }
    } else {
        FOR (i, min(val, s[idx]) + 1) {
            if (idx > 0 && s[idx] == s[idx - 1] && i < last) {
                continue;
            }
            if (i > 1) {
                nv.pb(i);
            }
            if (s[idx] - i > 1) {
                nv.pb(s[idx] - i);
            }
            split(s, idx + 1, val - i, x, nxt, i, a, nv, vis);
            if (i > 1) {
                nv.pop_back();
            }
            if (s[idx] - i > 1) {
                nv.pop_back();
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ll> a(m);
    FOR (i, m) {
        cin >> a[i];
        a[i] = min(a[i], n - a[i]);
    }
    ssort(a);
    set<vector<ll>> vis;
    vector<vector<ll>> cur({{n}});
    vis.insert({n});
    ll rv = 0;
    FORE (v, a) {
        vector<vector<ll>> nxt;
        FORE (s, cur) {
            ll x = n;
            FORE (w, s) {
                x -= w;
            }
            rv = max(rv, x);
            vector<ll> nv;
            split(s, 0, v, x, nxt, -1, a, nv, vis);
        }
        swap(cur, nxt);
    }
    FORE (s, cur) {
        ll x = n;
        FORE (v, s) {
            x -= v;
        }
        rv = max(rv, x);
    }
    cout << rv << '\n';

    return 0;
}