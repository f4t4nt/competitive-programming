#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 998244353;

struct Numerics {
    const ll MAXFAC = 64, MAXB = 17, MAXK, MAXA;

    vector<ll> fact, invfact, Bval, spf;
    vector<vector<ll>> polyA;

    Numerics(ll MAXK = 1e5, ll MAXA = 16) : MAXK(MAXK), MAXA(MAXA) {
        buildFactorials();
        buildBernoulli();
        buildSpf();
        buildPolyA();
    }

    ll poww(ll a, ll b) {
        ll rv = 1;
        while (b) {
            if (b & 1) rv = rv * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return rv;
    }

    ll inv(ll x) {
        return poww(x, MOD - 2);
    }

    void buildFactorials() {
        fact.resize(MAXFAC + 1);
        invfact.resize(MAXFAC + 1);
        fact[0] = 1;
        for (ll i = 1; i <= MAXFAC; i++) {
            fact[i] = fact[i - 1] * i % MOD;
        }
        invfact[MAXFAC] = inv(fact[MAXFAC]);
        for (ll i = MAXFAC - 1; i >= 0; i--) {
            invfact[i] = invfact[i + 1] * (i + 1) % MOD;
        }
    }

    ll binom(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
    }

    ll modInv(ll a, ll m = MOD) {
        return poww(a, m - 2);
    }

    ll frac(ll num, ll den) {
        num = (num % MOD + MOD) % MOD;
        den = (den % MOD + MOD) % MOD;
        return (num * modInv(den)) % MOD;
    }

    void buildBernoulli() {
        Bval.resize(MAXB);
        Bval[0] = 1;
        Bval[1] = frac(1, 2);
        Bval[2] = frac(1, 6);
        Bval[3] = 0;
        Bval[4] = frac(-1, 30);
        Bval[5] = 0;
        Bval[6] = frac(1, 42);
        Bval[7] = 0;
        Bval[8] = frac(-1, 30);
        Bval[9] = 0;
        Bval[10] = frac(5, 66);
        Bval[11] = 0;
        Bval[12] = frac(-691, 2730);
        Bval[13] = 0;
        Bval[14] = frac(7, 6);
        Bval[15] = 0;
        Bval[16] = frac(-3617, 510);
    }

    ll sumOfPowers(ll n, ll m) {
        ll s = 0;
        for (ll j = 0; j <= m; j++) {
            if (Bval[j] == 0) continue;
            ll c = binom(m + 1, j);
            ll p = poww(n, m + 1 - j);
            ll term = c % MOD;
            term = (term * Bval[j]) % MOD;
            term = (term * p) % MOD;
            s = (s + term) % MOD;
        }
        s = (s * modInv(m + 1)) % MOD;
        return (s + MOD) % MOD;
    }

    void buildSpf() {
        spf.resize(MAXK + 1);
        for (ll i = 2; i <= MAXK; i++) {
            spf[i] = 0;
        }
        for (ll p = 2; p * p <= MAXK; p++) {
            if (spf[p] == 0) {
                for (ll multiple = (ll)p * p; multiple <= MAXK; multiple += p) {
                    if (spf[multiple] == 0) {
                        spf[multiple] = p;
                    }
                }
            }
        }
        for (ll i = 2; i <= MAXK; i++) {
            if (spf[i] == 0) spf[i] = i;
        }
        spf[1] = 0;
    }

    vector<pll> factorize(ll x) {
        vector<pll> res;
        if (x <= 1) return res;
        while (x > 1) {
            ll p = spf[x];
            ll cnt = 0;
            while (spf[x] == p) {
                x /= p;
                cnt++;
            }
            res.pb({p, cnt});
        }
        return res;
    }

    vector<ll> polyMul(const vector<ll> &A, const vector<ll> &B) {
        ll degA = sz(A) - 1;
        ll degB = sz(B) - 1;
        ll degC = degA + degB;
        vector<ll> C(degC + 1, 0LL);
        for (ll i = 0; i <= degA; i++) {
            ll ai = A[i];
            if (ai == 0) continue;
            for (ll j = 0; j <= degB; j++) {
                ll val = (ai * B[j]) % MOD;
                C[i + j] = (C[i + j] + val) % MOD;
            }
        }
        return C;
    }

    void buildPolyA() {
        polyA.resize(MAXA + 1, vector<ll>(MAXA + 1));
        for (ll a = 1; a <= MAXA; a++) {
            vector<ll> poly(a + 1);
            poly[0] = 1;
            for (ll j = 0; j < a; j++) {
                vector<ll> tmp(sz(poly) + 1, 0LL);
                for (ll i = 0; i < sz(poly); i++) {
                    tmp[i + 1] = (tmp[i + 1] + poly[i]) % MOD;
                    ll val = (j * poly[i]) % MOD;
                    tmp[i] = (tmp[i] + val) % MOD;
                }
                poly = tmp;
            }
            ll invFa = invfact[a];
            for (ll i = 0; i < sz(poly); i++) {
                poly[i] = (poly[i] * invFa) % MOD;
            }
            for (ll i = 0; i <= a; i++) {
                polyA[a][i] = poly[i];
            }
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll tt; cin >> tt;
    vector<pll> queries(tt);
    ll max_k = 0;
    FOR(i, tt) {
        cin >> queries[i].x >> queries[i].y;
        max_k = max(max_k, queries[i].x);
    }

    Numerics numerics(max_k);
    vector<vector<ll>> polyOf(max_k + 1);
    vector<ll> degOf(max_k + 1);

    polyOf[1] = {1};
    degOf[1] = 0;
    for (ll x = 2; x <= max_k; x++) {
        auto fac = numerics.factorize(x);
        vector<ll> poly(1, 1);
        ll dsum = 0;
        for (auto &pf : fac) {
            ll e = pf.y;
            dsum += e;
            vector<ll> base(e + 1);
            for (ll i = 0; i <= e; i++) {
                base[i] = numerics.polyA[e][i];
            }
            poly = numerics.polyMul(poly, base);
        }
        polyOf[x] = poly;
        degOf[x] = dsum;
    }

    FOR (t, tt) {
        ll k = queries[t].x, n = queries[t].y;
        ll md = 0;
        for (ll x = 1; x <= k; x++) {
            if (degOf[x] > md) {
                md = degOf[x];
            }
        }
        vector<ll> sumPow(md + 1);
        FOR (m, md + 1) {
            sumPow[m] = numerics.sumOfPowers(n, m);
        }
        for (ll x = 1; x <= k; x++) {
            ll ans = 0, deg = degOf[x];
            auto &poly = polyOf[x];
            for (ll m = 0; m <= deg; m++) {
                ll c = poly[m];
                if (c == 0) continue;
                ll val = (c * sumPow[m]) % MOD;
                ans = (ans + val) % MOD;
            }
            cout << ans << ' ';
        }
        cout << '\n';
    }

    return 0;
}