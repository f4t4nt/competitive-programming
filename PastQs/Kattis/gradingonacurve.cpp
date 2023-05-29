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

bool valid(vector<ld> &s, ld k) {
    vector<ld> bin(3);
    FORE (x, s) {
        ld g = (ld) x / k;
        if (g >= 0.9) {
            bin[0]++;
        }
        if (g >= 0.8) {
            bin[1]++;
        }
        if (g >= 0.7) {
            bin[2]++;
        }
    }
    FOR (i, 3) {
        bin[i] /= sz(s);
    }
    return bin[0] >= 0.25 && bin[1] >= 0.5 && bin[2] >= 0.75;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld n, t;
    cin >> n >> t;
    t *= 2;
    vector<ld> s(n);
    FOR (i, n) {
        cin >> s[i];
    }
    if (!valid(s, 1)) {
        cout << -1 << '\n';
        return 0;
    }
    ll lo = 1, hi = t;
    while (lo < hi) {
        ll mid = (hi + lo + 1) / 2;
        if (valid(s, mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    cout << lo << '\n';

    return 0;
}