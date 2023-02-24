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
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

pair<ll, ll> manacher(str &s) {
    str t = "$#";
    FORE (c, s) {
        t += c;
        t += '#';
    }

    ll n = sz(t);
    ll center = 0, max_rad = -1, rad;
    vector<ll> p(n);
    FOR (i, n) {
        if (i <= max_rad) {
            rad = min(p[2 * center - i], max_rad - i);
        } else {
            rad = 0;
        }
        while (i - rad - 1 >= 0 && i + rad + 1 < n && t[i - rad - 1] == t[i + rad + 1]) {
            rad++;
        }
        p[i] = rad;
        if (i + rad > max_rad) {
            center = i;
            max_rad = i + rad;
        }
    }

    ll len = 0, idx = 0;
    FOR (i, n) {
        if (p[i] > len) {
            len = p[i];
            idx = i;
        }
    }

    return {len, (idx - len) / 2};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    str s;
    cin >> s;
    ll len, idx;
    tie(len, idx) = manacher(s);
    cout << s.substr(idx, len) << '\n';

    return 0;
}