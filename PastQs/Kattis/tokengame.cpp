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

constexpr ll MAX_N = 300;
vector<vector<ll>> dp1(MAX_N + 1, vector<ll>(MAX_N + 1, -1)),
    dp2(MAX_N + 1, vector<ll>(2 * MAX_N + 1, -1));

ll nim(ll x1, ll x2) {
    if (abs(x1 - x2) <= 1) {
        return 0;
    }
    ll rv = dp1[x1][x2];
    if (rv != -1) {
        return rv;
    }
    vector<bool> ref(2 * MAX_N + 1, false);
    FOR (x, x1) {
        ref[nim(x, x2)] = true;
    }
    FOR (x, x2) {
        ref[nim(x1, x)] = true;
    }
    ll i = 0;
    while (ref[i]) {
        i++;
    }
    dp1[x1][x2] = i;
    return i;
}

ll g(ll x2, ll a) {
    ll rv = dp2[x2][a];
    if (rv != -1) {
        return rv;
    }
    rv = 1e9;
    FORR (x, MAX_N + 1) {
        if (nim(x, x2) == a) {
            rv = x;
        }
    }
    dp2[x2][a] = rv;
    return rv;
}

bool f(ll x1, ll y1, ll x2, ll y2) {
    if (y1 == y2) {
        return x1 > (x2 + 1);
    }
    if (abs(y1 - y2) == 1) {
        return x1 > x2;
    }
    return x1 > g(x2, nim(y1, y2));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        ll d = abs(x1 - x2) + abs(y1 - y2);
        if (d == 1) {
            cout << 0 << '\n';
            continue;
        }
        ll rv = 0;
        FOR (_, 4) {
            rv += f(x1, y1, x2, y2);
            swap(x1, y1);
            swap(y1, x2);
            swap(x2, y2);
        }
        cout << rv << '\n';
    }

    return 0;
}