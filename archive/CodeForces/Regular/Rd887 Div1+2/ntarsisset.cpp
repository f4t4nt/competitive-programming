#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
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

ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

ll count_sols(ll a, ll b, ll c) {
    ll g = gcd(a, b);
    if (c % g != 0) {
        return 0;
    }
    a /= g;
    b /= g;
    c /= g;
    ll rv = 0;
    FOR (x, 2e5 + 10) {
        ll tmp = c - a * x,
            rem = tmp % b,
            y = tmp / b;
        if (rem == 0 && y >= 0) {
            rv++;
        }
        if (tmp < 0) {
            break;
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<ll> fib(2e5 + 10);
    fib[0] = 0;
    fib[1] = 1;
    FOB (i, 2, 2e5 + 10) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    ll t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        // FOR (a, 10000) {
        //     FOR (b, 10000) {
        //         if (n == fib[k - 1] * a + fib[k] * b) {
        //             rv++;
        //         }
        //     }
        // }
        if (k > 2e5) {
            cout << 0 << '\n';
            continue;
        }
        ll rv = count_sols(fib[k - 1], fib[k], n);
        cout << rv << '\n';
    }

    return 0;
}