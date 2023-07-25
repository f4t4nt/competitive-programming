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

ll pow10(ll e) {
    ll x = 10, rv = 1;
    while (e) {
        if (e & 1) {
            rv *= x;
        }
        x *= x;
        e >>= 1;
    }
    return rv;
}

ch get_kth(ll k) {
    ll cur = 0, len = 1;
    while (cur + len * 9 * pow10(len - 1) < k) {
        cur += len * 9 * pow10(len - 1);
        len++;
    }
    ll num = pow10(len - 1) + (k - cur - 1) / len;
    return to_string(num)[(k - cur - 1) % len];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        ch rv = get_kth(k);
        cout << rv << '\n';
    }

    return 0;
}