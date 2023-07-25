#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

ll bonus[10][4] = {
    {0,0,0,0},      // 0 na
    {0,2,6,14},     // 1
    {0,4,12,18},    // 2
    {0,6,8,12},     // 3
    {0,8,14,16},    // 4
    {0,0,0,0},      // 5 na
    {0,2,6,14},     // 6
    {0,4,12,18},    // 7
    {0,6,8,12},     // 8
    {0,8,14,16}     // 9
};

ll f(ll s, ll k, ll a) {
    ll b = k - a, rv = s * b, pre = 0, mid = 0, post = 0;
    if (a > 0) {
        pre += s % 10;
        a--;
    }
    mid += 20 * (a / 4);
    a %= 4;
    post += bonus[s % 10][a];
    ll xtra = pre + mid + post;
    rv += xtra * b;
    return rv;
}

ll solve(ll s, ll k) {
    ll l = (5 * k - s) / 10, r = l;
    l = max(0LL, l - 10), r = min(k, r + 10);
    ll ref = 0, rv = 0;
    FOR (a, min(10LL, k)) {
        ll tmp = f(s, k, a);
        if (tmp > rv) {
            rv = tmp;
            ref = a;
        }
    }
    FOB (a, l, r + 1) {
        ll tmp = f(s, k, a);
        if (tmp > rv) {
            rv = tmp;
            ref = a;
        }
    }
    return rv;
}

ll ternary(ll s, ll k) {
    ll l = 0, r = k;
    while (r - l > 2) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;
        if (f(s, k, m1) < f(s, k, m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    l = max(0LL, l - 50000);
    r = min(k, r + 50000);
    ll ref = 0;
    ll rv = 0;
    FOB (a, l, r + 1) {
        if (f(s, k, a) > rv) {
            rv = f(s, k, a);
            ref = a;
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll s, k, rv;
        cin >> s >> k;
        if (s % 10 == 0) {
            rv = s * k;
        } elif (s % 10 == 5) {
            rv = max(s * k, (s + 5) * (k - 1));
        } else {
            rv = solve(s, k);
        }
        cout << rv << '\n';
    }

    return 0;
}