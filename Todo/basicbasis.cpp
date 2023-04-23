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

// https://open.kattis.com/problems/basicbasis

struct LongHex {
    ll k;
    vector<ll> v;
    LongHex(ll k) : k(k) {}
    void init() {
        v = vector<ll>(k);
        FOR (i, k) {
            ch c;
            cin >> c;
            if (c >= '0' && c <= '9') {
                v[i] = c - '0';
            } else {
                v[i] = c - 'a' + 10;
            }
        }
    }

    LongHex operator^(const LongHex &other) const {
        LongHex rv(k);
        FOR (i, k) {
            rv.v[i] = v[i] ^ other.v[i];
        }
        return rv;
    }

    bool operator==(const LongHex &other) const {
        FOR (i, k) {
            if (v[i] != other.v[i]) {
                return false;
            }
        }
        return true;
    }

    void operator>>=(ll n) {
        FOR (i, k) {
            v[i] >>= n;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q, k;
    cin >> n >> q >> k;
    vector<LongHex> a(n, LongHex(k));
    FOR (i, n) {
        a[i].init();
    }
    while (q--) {
        LongHex b(k);
        b.init();
    }

    return 0;
}