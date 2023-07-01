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

vector<str> words;
map<str, vector<ll>> idxs;

ll init() {
    str w;
    ll i = 0;
    while (cin >> w) {
        words.pb(w);
        idxs[w].pb(i);
        i++;
    }
    return i;
}

set<str> get_adj(str &s) {
    set<str> rv;
    FOR (i, sz(s)) {
        str t = s;
        t[i] = '*';
        rv.insert(t);
    }
    FOR (i, sz(s) + 1) {
        str t = s;
        t.insert(i, "*");
        rv.insert(t);
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n = init();
    vector<vector<ll>> adj(n);
    map<str, ll> active;
    FORE (w, words) {
        auto adjw = get_adj(w);
        map<str, ll> tmp;
        ll best = 0;
        FORE (aw, adjw) {
            tmp[aw] = active[aw] + 1;
            best = max(best, tmp[aw]);
        }
        FORE (e, tmp) {
            active[e.first] = best;
        }
    }
    ll rv = 0;
    FORE (e, active) {
        rv = max(rv, e.second);
    }
    cout << rv << '\n';

    return 0;
}