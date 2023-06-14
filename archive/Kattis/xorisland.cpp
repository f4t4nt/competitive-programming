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

ll bitcount(ll x) {
    ll rv = 0;
    while (x) {
        x &= x - 1;
        rv++;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
    }

    vector<ll> triples;
    FOR (i, n) {
        FOR (j, i) {
            FOB (k, j + 1, i) {
                if ((a[i] ^ a[j]) == a[k]) {
                    triples.pb((1LL << i) | (1LL << j) | (1LL << k));
                }
            }
        }
    }
    ssort(triples);

    ll rv = 0;
    // vector<bool> valid(1 << n, true);
    FOR (i, (1 << n)) {
        // FORE (t, triples) {
        //     valid[i | t] = false;
        // }
        // if (valid[i]) {
        //     rv = max(rv, bitcount(i));
        // }
        bool valid = true;
        FORE (t, triples) {
            if ((i & t) == t) {
                valid = false;
                break;
            }
        }
        if (valid) {
            rv = max(rv, bitcount(i));
        }
    }
    cout << n - rv << '\n';

    return 0;
}