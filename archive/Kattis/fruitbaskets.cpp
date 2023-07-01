#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
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
    ll rv = 0;
    FOR (i, n) {
        rv += a[i] * (1LL << (n - 1));
    }
    multiset<ll> ref = {0};
    FOR (i, n) {
        if (a[i] >= 200) {
            continue;
        }
        multiset<ll> tmp;
        FORE (j, ref) {
            if (j + a[i] < 200) {
                tmp.insert(j + a[i]);
            }
        }
        FORE (j, tmp) {
            ref.insert(j);
        }
    }
    FORE (i, ref) {
        rv -= i;
    }
    // FOR (i, n) {
    //     if (a[i] < 200) {
    //         rv -= a[i];
    //     }
    //     FOB (j, i + 1, n) {
    //         if (a[i] + a[j] < 200) {
    //             rv -= a[i] + a[j];
    //         }
    //         FOB (k, j + 1, n) {
    //             if (a[i] + a[j] + a[k] < 200) {
    //                 rv -= a[i] + a[j] + a[k];
    //             }
    //         }
    //     }
    // }
    assert(rv >= 0);
    cout << rv << '\n';

    return 0;
}