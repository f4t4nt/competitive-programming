#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 1e9 + 7;

struct mll {
    ll v;
    mll(): v(0) {}
    mll(ll _v) { v = (_v % MOD + MOD) % MOD; }
    explicit operator ll() const { return v; }
    mll& operator+=(const mll &o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    mll& operator-=(const mll &o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    mll& operator*=(const mll &o) { v = (ll)(v * o.v % MOD); return *this; }
    mll& operator/=(const mll &o) { return *this *= o.inv(); }
    friend mll operator+(mll a, const mll &b) { return a += b; }
    friend mll operator-(mll a, const mll &b) { return a -= b; }
    friend mll operator*(mll a, const mll &b) { return a *= b; }
    friend mll operator/(mll a, const mll &b) { return a /= b; }
    mll operator-() const { return mll(-v); }
    bool operator==(const mll &o) const { return v == o.v; }
    bool operator!=(const mll &o) const { return v != o.v; }
    static mll pow(mll a, ll e) {
        mll r = 1;
        while (e > 0) {
            if (e & 1) r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }
    mll inv() const { return pow(*this, MOD - 2); }
    friend ostream& operator<<(ostream &os, const mll &m) { return os << m.v; }
    friend istream& operator>>(istream &is, mll &m) { ll x; is >> x; m = mll(x); return is; }
};

ll gauss_jordan_mod(vector<vector<mll>> &A,
                    vector<mll>         &b,
                    vector<mll>         &x)
{
    const ll n = sz(A), m = sz(A[0]);

    vector<vector<mll>> a(n, vector<mll>(m + 1));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) a[i][j] = A[i][j];
        a[i][m] = b[i];
    }

    vector<ll> where(m, -1);

    for (ll col = 0, row = 0; col < m && row < n; col++) {
        ll sel = -1;
        for (ll i = row; i < n; i++)
            if (a[i][col].v != 0) { sel = i; break; }
        if (sel == -1) continue;

        swap(a[sel], a[row]);
        where[col] = row;

        mll inv_pivot = a[row][col].inv();
        for (ll j = col; j <= m; j++) a[row][j] *= inv_pivot;

        for (ll i = 0; i < n; i++) if (i != row && a[i][col].v != 0) {
            mll factor = a[i][col];
            for (ll j = col; j <= m; j++) a[i][j] -= factor * a[row][j];
        }
        row++;
    }

    x.assign(m, 0);
    for (ll i = 0; i < m; i++)
        if (where[i] != -1) x[i] = a[where[i]][m];

    for (ll i = 0; i < n; i++) {
        mll sum = 0;
        for (ll j = 0; j < m; j++) sum += A[i][j] * x[j];
        if (sum != b[i]) return 0;
    }

    for (ll i = 0; i < m; i++)
        if (where[i] == -1) return -1;

    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<vector<mll>> A(n, vector<mll>(m));
    vector<mll> b(n);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> A[i][j];
        cin >> b[i];
    }
    vector<mll> x;
    ll res = gauss_jordan_mod(A, b, x);
    if (res == 0) cout << -1 << '\n';
    else {
        for (mll xx : x) cout << xx << ' ';
        cout << '\n';
    }


    return 0;
}
