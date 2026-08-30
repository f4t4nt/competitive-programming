#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sz(C) (ll) C.size()

const ld EPS = 1e-8;
const ld INF = 1e18;

// -----------------------------------------------------------------------------
//  Simplex (two-phase LP)
// -----------------------------------------------------------------------------
//  Solves:      max c.x subject to Ax <= b, x >= 0 (b may be negative)
//  Usage:      Simplex lp(A, b, c);       A is m x n
//              vector<ld> x;
//              ld v = lp.solve(x);        optimum; x holds an argmax
//  Returns:    -INF infeasible, INF unbounded, else the optimal value.
//  Complexity: O((m + n) * #pivots), exponential worst case, fast in practice.
//  Notes:      - equality constraint = pair of <= and >=; free variable =
//                difference of two nonnegative ones; minimize = negate c.
//              - all long double; expect ~EPS noise, keep inputs sanely scaled.
// -----------------------------------------------------------------------------
struct Simplex {
    ll m, n;                // constraints, variables
    vector<ll> N, B;        // nonbasic / basic variable ids
    vector<vector<ld>> D;   // tableau, (m + 2) x (n + 2)

    Simplex(vector<vector<ld>> &A, vector<ld> &b, vector<ld> &c) :
        m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vector<ld>(n + 2)) {
        for (ll i = 0; i < m; i++) for (ll j = 0; j < n; j++) D[i][j] = A[i][j];
        for (ll i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
        for (ll j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
        N[n] = -1; D[m + 1][n] = 1;
    }

    void pivot(ll r, ll s) {
        ld inv = 1 / D[r][s];
        for (ll i = 0; i < m + 2; i++) if (i != r)
            for (ll j = 0; j < n + 2; j++) if (j != s)
                D[i][j] -= D[r][j] * D[i][s] * inv;
        for (ll j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
        for (ll i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    // pivot until objective row x has no improving column; false if unbounded
    bool simplex(ll phase) {
        ll x = m + phase - 1;
        for (;;) {
            ll s = -1;
            for (ll j = 0; j < n + 1; j++) if (N[j] != -phase)
                if (s == -1 || make_pair(D[x][j], N[j]) < make_pair(D[x][s], N[s])) s = j;
            if (D[x][s] >= -EPS) return true;
            ll r = -1;
            for (ll i = 0; i < m; i++) {
                if (D[i][s] <= EPS) continue;
                if (r == -1 || make_pair(D[i][n + 1] / D[i][s], B[i]) <
                               make_pair(D[r][n + 1] / D[r][s], B[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    // phase 1 to find a feasible point if needed, phase 2 to optimize
    ld solve(vector<ld> &x) {
        ll r = 0;
        for (ll i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -EPS) {
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -EPS) return -INF;
            for (ll i = 0; i < m; i++) if (B[i] == -1) {
                ll s = 0;
                for (ll j = 1; j < n + 1; j++) if (D[i][j] < D[i][s]) s = j;
                pivot(i, s);
            }
        }
        bool ok = simplex(1);
        x = vector<ld>(n);
        for (ll i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return ok ? D[m][n + 1] : INF;
    }
};
