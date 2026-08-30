#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

// -----------------------------------------------------------------------------
//  Matrix
// -----------------------------------------------------------------------------
//  Supports:   - a * b     product (a is n x m, b is m x k)
//              - a ^ p     fast exponentiation (square only, p >= 0)
//              - det()     determinant, elimination on an ld copy
//              - inv()     inverse, floating T only (rows get divided)
//  Complexity:  * is O(n m k), ^ is O(n^3 log p), det / inv O(n^3)
//  Notes:      - no overflow guard on T = ll; use T = mll (number_theory.h)
//                for modular, T = ld if entries outgrow ll
//              - det() / inv() are numeric, not for T = mll
// -----------------------------------------------------------------------------
template<class T = ll>
struct Matrix {
    ll n, m;                // rows, cols
    vector<vector<T>> mat;  // mat[i] is row i

    Matrix(ll _n, ll _m) : n(_n), m(_m), mat(n, vector<T>(m)) {}

    Matrix operator*(const Matrix &other) const {
        Matrix rv(n, other.m);
        for (ll i = 0; i < n; i++)
            for (ll k = 0; k < m; k++)
                for (ll j = 0; j < other.m; j++)
                    rv.mat[i][j] += mat[i][k] * other.mat[k][j];
        return rv;
    }

    Matrix operator^(ll p) const {
        Matrix rv(n, n), a = *this;
        for (ll i = 0; i < n; i++) rv.mat[i][i] = 1;
        while (p) {
            if (p & 1) rv = rv * a;
            a = a * a;
            p >>= 1;
        }
        return rv;
    }

    ld det() const {
        vector<vector<ld>> a(n, vector<ld>(n));
        for (ll i = 0; i < n; i++)
            for (ll j = 0; j < n; j++) a[i][j] = (ld) mat[i][j];
        ld rv = 1;
        for (ll i = 0; i < n; i++) {
            ll p = i;
            for (ll j = i + 1; j < n; j++) if (fabsl(a[j][i]) > fabsl(a[p][i])) p = j;
            if (p != i) swap(a[i], a[p]), rv *= -1;
            if (fabsl(a[i][i]) < 1e-9) return 0;
            rv *= a[i][i];
            for (ll j = i + 1; j < n; j++) {
                ld c = a[j][i] / a[i][i];
                for (ll k = i; k < n; k++) a[j][k] -= c * a[i][k];
            }
        }
        return rv;
    }

    // floating T only
    Matrix inv() const {
        Matrix a = *this, rv(n, n);
        for (ll i = 0; i < n; i++) rv.mat[i][i] = 1;
        for (ll i = 0; i < n; i++) {
            ll p = i;
            for (ll j = i + 1; j < n; j++) if (fabsl(a.mat[j][i]) > fabsl(a.mat[p][i])) p = j;
            if (p != i) {
                swap(a.mat[i], a.mat[p]);
                swap(rv.mat[i], rv.mat[p]);
            }
            T c = a.mat[i][i];
            for (ll j = 0; j < n; j++) a.mat[i][j] /= c, rv.mat[i][j] /= c;
            for (ll j = 0; j < n; j++) if (j != i) {
                c = a.mat[j][i];
                for (ll k = 0; k < n; k++) a.mat[j][k] -= c * a.mat[i][k], rv.mat[j][k] -= c * rv.mat[i][k];
            }
        }
        return rv;
    }
};

// -----------------------------------------------------------------------------
//  Min-plus variant
// -----------------------------------------------------------------------------
//  (*, +) becomes (min, +), identity is the 0-diagonal matrix.
//  a ^ p = min-cost walks with exactly p edges (INF = no edge).
// -----------------------------------------------------------------------------
const ll INF = 4e18;

struct MinPlusMatrix {
    ll n, m;
    vector<vector<ll>> mat;

    MinPlusMatrix(ll _n, ll _m) : n(_n), m(_m), mat(n, vector<ll>(m, INF)) {}

    MinPlusMatrix operator*(const MinPlusMatrix &other) const {
        MinPlusMatrix rv(n, other.m);
        for (ll i = 0; i < n; i++)
            for (ll k = 0; k < m; k++) if (mat[i][k] != INF)
                for (ll j = 0; j < other.m; j++) if (other.mat[k][j] != INF)
                    rv.mat[i][j] = min(rv.mat[i][j], mat[i][k] + other.mat[k][j]);
        return rv;
    }

    MinPlusMatrix operator^(ll p) const {
        MinPlusMatrix rv(n, n), a = *this;
        for (ll i = 0; i < n; i++) rv.mat[i][i] = 0;
        while (p) {
            if (p & 1) rv = rv * a;
            a = a * a;
            p >>= 1;
        }
        return rv;
    }
};
