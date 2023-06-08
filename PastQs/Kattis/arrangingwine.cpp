#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

constexpr ll MOD = 1e9 + 7;
constexpr ll MAX = 2e6 + 1;
vector<ll> fact(MAX, 1);
vector<ll> inv(MAX, 1); 

ll pow(ll x, ll p) {
    ll rv = 1;
    while(p) {
        if(p & 1) rv = rv * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return rv;
}

ll choose(ll n, ll k) {
    if (k > n) {
        return 0;
    }
    return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOB (i, 1, MAX) {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = pow(fact[i], MOD - 2);
    }

    ll r, w, d;
    cin >> r >> w >> d;
    ll rv = 0;
    FOR (i, w + 2) {
        if (w + r < d * i) {
            break;
        }
        ll tmp = choose(w + 1, i) * choose(w + r - (d + 1) * i, w) % MOD;
        if (i % 2 == 0) {
            rv = (rv + tmp) % MOD;
        } else {
            rv = (rv - tmp + MOD) % MOD;
        }
    }
    cout << rv << '\n';

    return 0;
}