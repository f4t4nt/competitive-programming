#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

void reduce(ll &a, ll &b) {
    if (a == 0) {
        b = 1;
        return;
    }
    ll g = __gcd(a, b);
    a /= g;
    b /= g;
    if (b < 0) {
        a *= -1;
        b *= -1;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, b, n;
    cin >> a >> b >> n;
    ll x = 0, y = b;
    FOR (i, n + 1) {
        ll dx = 2 * a - x % (2 * a);
        ll dy = 2 * b - y % (2 * b);
        ll d = min(dx, dy);
        x = (x + d) % (4 * a);
        y = (y + d) % (4 * b);
    }
    x -= a;
    y -= b;
    if (x > a) {
        x = 2 * a - x;
    }
    if (y > b) {
        y = 2 * b - y;
    }
    reduce(x, a);
    reduce(y, b);
    cout << x << ' ' << a << ' ' << y << ' ' << b << '\n';

    return 0;
}