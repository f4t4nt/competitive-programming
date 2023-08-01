#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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

ch try_insert(str &s, str &t) {
    if (sz(s) + 1 != sz(t)) {
        return '.';
    }
    FOR (i, sz(s)) {
        if (s[i] != t[i + 1]) {
            return '.';
        }
    }
    return t[0];
}

vector<ll> get_diff(str &s, str &t) {
    vector<ll> rv;
    FOR (i, sz(s)) {
        if (s[i] != t[i]) {
            rv.pb(i);
        }
    }
    return rv;
}

str solution(str &s, str &t) {
    if (s == t) {
        return "NOTHING";
    }
    ch c = try_insert(s, t);
    if (c != '.') {
        return "INSERT " + str(1, c);
    }
    if (sz(s) == sz(t)) {
        vector<ll> diff = get_diff(s, t);
        if (sz(diff) == 1) {
            return "CHANGE " + str(1, s[diff[0]]) + " " + str(1, t[diff[0]]);
        }
        if (sz(diff) == 2 && s[diff[0]] == t[diff[1]] && s[diff[1]] == t[diff[0]]) {
            return "SWAP " + str(1, s[diff[0]]) + " " + str(1, s[diff[1]]);
        }
    }
    return "IMPOSSIBLE";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    str s, t;
    cin >> s >> t;
    cout << solution(s, t) << '\n';

    return 0;
}