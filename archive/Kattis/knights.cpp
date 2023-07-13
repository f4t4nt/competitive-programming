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

constexpr ll MOD = 1e9 + 9;
ll kx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
ll ky[] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct Matrix {
    vector<vector<ll>> mat;
    ll n, m;

    Matrix(ll n, ll m) : n(n), m(m) {
        mat.resize(n, vector<ll>(m));
    }

    Matrix(vector<vector<ll>> mat) : mat(mat), n(sz(mat)), m(sz(mat[0])) {}

    Matrix operator*(const Matrix &other) const {
        Matrix rv(n, other.m);
        FOR(i, n) {
            FOR(j, other.m) {
                FOR(k, m) {
                    rv.mat[i][j] += mat[i][k] * other.mat[k][j];
                    rv.mat[i][j] %= MOD;
                }
            }
        }
        return rv;
    }

    Matrix operator^(ll p) const {
        Matrix rv(n, n);
        FOR(i, n) {
            rv.mat[i][i] = 1;
        }
        Matrix a = *this;
        while (p) {
            if (p & 1) {
                rv = rv * a;
            }
            a = a * a;
            p >>= 1;
        }
        return rv;
    }
};

bool valid(ll x, ll &n, ll &m) {
    set<pair<ll, ll>> s;
    FOR (i, m) {
        FOR (j, n) {
            if (x & 1) {
                FOR (l, 4) {
                    ll nx = i + kx[l];
                    ll ny = j + ky[l];
                    if (s.count({nx, ny})) {
                        return false;
                    }
                }
                s.insert({i, j});
            }
            x >>= 1;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    ll m2 = min(m, 3LL);
    vector<ll> ref;
    FOR (i, 1LL << (n * m2)) {
        if (valid(i, n, m2)) {
            ref.pb(i);
        }
    }
    if (m == m2) {
        cout << sz(ref) << '\n';
        return 0;
    }
    ll mask = (1LL << (2 * n)) - 1;
    map<ll, ll> mp;
    FORE (x, ref) {
        ll a = x & mask, b = x >> n;
        if (!mp.count(a)) {
            mp[a] = sz(mp);
        }
        if (!mp.count(b)) {
            mp[b] = sz(mp);
        }
    }
    Matrix vec(sz(mp), 1);
    Matrix mat(sz(mp), sz(mp));
    FORE (x, ref) {
        ll a = x & mask, b = x >> n;
        vec.mat[mp[a]][0] = 1;
        mat.mat[mp[a]][mp[b]] = 1;
    }
    mat = mat ^ (m - m2 + 1);
    Matrix res = mat * vec;
    ll rv = 0;
    FOR (i, res.n) {
        rv += res.mat[i][0];
        rv %= MOD;
    }
    cout << rv << '\n';

    return 0;
}