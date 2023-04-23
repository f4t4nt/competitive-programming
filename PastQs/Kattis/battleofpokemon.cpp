#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

tuple<ll, ll, ll> solve(ll i, ll j) {
    ll p_a = 0, p_b = 0, a_cnt = i, b_cnt = i, s = 0;
    while (s < 2 * i && p_a + a_cnt >= p_b && p_b + b_cnt >= p_a) {
        ll tmp = j % 2;
        if (s % 2 == 0) {
            p_a += tmp;
            a_cnt--;
        } else {
            p_b += tmp;
            b_cnt--;
        }
        j /= 2;
        s++;
    }
    return {s, p_a, p_b};
}

ll cnt(ll x, ll len, set<ll> &ref) {
    ll rv = 0;
    FORE (y, ref) {
        if ((y & ((1 << len) - 1)) == (x & ((1 << len) - 1))) {
            rv++;
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<vector<tuple<ll, ll, ll>>> ref0(7);
    set<ll> ref1[7][13][7][7];
    FOB (i, 1, 7) {
        ref0[i] = vector<tuple<ll, ll, ll>>(1 << (2 * i));
        FOR (j, sz(ref0[i])) {
            auto tmp = solve(i, j);
            ref0[i][j] = tmp;
            ref1[i][get<0>(tmp)][get<1>(tmp)][get<2>(tmp)].insert(j & ((1 << get<0>(tmp)) - 1)); 
        }
    }

    ll t;
    cin >> t;
    while (t--) {
        ll i, j = 0;
        cin >> i;
        FOR (k, 2 * i) {
            ch c;
            cin >> c;
            j += (c == 'E') << k;
        }
        ll s, p_a, p_b;
        tie(s, p_a, p_b) = ref0[i][j];
        vector<ll> tmp(s + 1);
        FOR (k, s + 1) {
            tmp[k] = cnt(j, k, ref1[i][s][p_a][p_b]);
        }
        ll c = 0;
        while (tmp[c] != 1) {
            c++;
        }
        cout << s << ' ' << c << '\n';
    }

    return 0;
}