#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

// imma show YOU how great i am.

bool valid(str w1, str w2, map<set<str>, ll> &cnt) {
    if (sz(w1) != sz(w2)) {
        return false;
    }
    vector<ll> del;
    FOR (i, sz(w1)) {
        if (w1[i] != w2[i]) {
            del.pb(i);
        } else {
            w1[i] = ' ';
            w2[i] = ' ';
        }
    }
    if (sz(del) != 2) {
        return false;
    }
    if (del[0] + 1 != del[1]) {
        return false;
    }
    cnt[{w1, w2}]++;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<str> words(n);
    FORE (w, words) {
        cin >> w;
    }
    map<set<str>, ll> cnt;
    FOR (i, n) {
        FOB (j, i + 1, n) {
            valid(words[i], words[j], cnt);
        }
    }
    ll rv = 0;
    FORE (p, cnt) {
        if (p.second == 1) {
            rv++;
        }
    }
    cout << rv << '\n';

    return 0;
}