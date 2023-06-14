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

vector<ll> pow3(10, 1);

// 0123456789
// 012
// 345
// 678

// 012
// .XO

ll val(ll s, ll i) {
    return (s / pow3[i]) % 3;
}

ll set_(ll s, ll c, ll i) {
    return s += c * pow3[i];
}

bool won(ll c, ll s) {
    bool rv = false;
    FOR (i, 3) {
        rv |= (c == val(s, 3 * i) &&
            c == val(s, 3 * i + 1) &&
            c == val(s, 3 * i + 2));
    }
    FOR (i, 3) {
        rv |= (c == val(s, i) &&
            c == val(s, 3 + i) &&
            c == val(s, 6 + i));
    }
    rv |= (c == val(s, 0) &&
        c == val(s, 4) &&
        c == val(s, 8));
    rv |= (c == val(s, 2) &&
        c == val(s, 4) &&
        c == val(s, 6));
    return rv;
}

pair<ll, ll> dfs(ll s, ll c, vector<pair<ll, ll>> &ref) {
    if (won(1, s)) {
        ref[s] = {1, 0};
    } elif (won(2, s)) {
        ref[s] = {0, 1};
    } elif (ref[s].first == -1) {
        ref[s] = {0, 0};
        FOR (i, 9) {
            if (val(s, i) != 0) {
                continue;
            }
            ll t = set_(s, c, i);
            pair<ll, ll> tmp = dfs(t, 3 - c, ref);
            ref[s].first += tmp.first;
            ref[s].second += tmp.second; 
        }
    }
    return ref[s];
}

ll convert(str s) {
    ll rv = 0;
    FOR (i, 9) {
        rv *= 3;
        if (s[i] == 'X') {
            rv += 1;
        } elif (s[i] == 'O') {
            rv += 2;
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOB (i, 1LL, sz(pow3)) {
        pow3[i] = pow3[i - 1] * 3;
    }

    vector<pair<ll, ll>> ref(pow3[9], {-1, -1});
    dfs(0, 1, ref);

    ll t;
    cin >> t;
    while (t--) {
        str s;
        cin >> s;
        ll rv = convert(s);
        cout << ref[rv].first << ' ' << ref[rv].second << '\n';
    }

    return 0;
}