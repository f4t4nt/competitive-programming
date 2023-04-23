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

constexpr ll MOD = 998244353;
constexpr ll MAX_P = 23;

vector<ll> fact(1 << MAX_P, 1), inv(1 << MAX_P, 1);

ll pow(ll a, ll b) {
    ll rv = 1;
    while (b) {
        if (b & 1) {
            rv = (rv * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return rv;
}

void init() {
    FOB (i, 1, (1 << MAX_P)) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv[(1 << MAX_P) - 1] = pow(fact[(1 << MAX_P) - 1], MOD - 2);
    FORR (i, (1 << MAX_P) - 1) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
}

ll choose(ll n, ll k) {
    if (k > n) {
        return 0;
    }
    return (fact[n] * inv[k] % MOD) * inv[n - k] % MOD;
}

ll get_bitcnt(ll x) {
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

    init();
    ll n, k, m, m2 = 1;
    cin >> n >> k >> m;
    while (m >= m2) {
        m2 *= 2;
    }

    vector<ll> bitcnt(m2), cnt(m2);
    FOR (i, m2) {
        bitcnt[i] = get_bitcnt(i);
    }
    FOR (i, m + 1) {
        cnt[i] = 1;
    }

    for (ll x = 1; x < m2; x *= 2) {
        FOR (i, m2) {
            if ((i & x) == 0) {
                cnt[i] = (cnt[i] + cnt[i | x]) % MOD;
            }
        }
    }

    vector<ll> ref1(m2);
    FOR (i, m2) {
        ref1[i] = choose(cnt[i], n);
        if (bitcnt[i] & 1) {
            ref1[i] = (MOD - ref1[i]) % MOD;
        }
    }
    
    vector<ll> ref2 = ref1;
    for (ll x = 1; x < m2; x *= 2) {
        FOR (i, m2) {
            if ((i & x) == 0) {
                ref2[i] = (ref2[i] + ref2[i | x]) % MOD;
            }
        }
    }

    FOR (i, m2) {
        if (bitcnt[i] & 1) {
            ref2[i] = (MOD - ref2[i]) % MOD;
        }
    }

    ll rv = 0;
    FOB (i, (1 << k) - 1, m + 1) {
        if (bitcnt[i] >= k) {
            rv = (rv + ref2[i]) % MOD;
        }
    }

    rv = (rv * fact[n]) % MOD;
    cout << rv << '\n';

    return 0;
}