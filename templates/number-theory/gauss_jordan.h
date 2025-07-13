#include <bits/stdc++.h>
#include "number_theory.h"
using namespace std;

typedef long long ll;
typedef long double ld;

#define pb push_back
#define sz(C) (ll) C.size()

const ld EPS = 1e-12;

// Gauss-Jordan elimination, returns 0 if no solution, 1 if unique, -1 if infinitely many
// Solves Ax = b for x
ll gauss_jordan_ld(vector<vector<ld>> &A, // n rows by m columns coefficient matrix
                   vector<ld>         &b, // n RHS values
                   vector<ld>         &x) // m-sized solution
{
    const ll n = sz(A), m = sz(A[0]);

    // build augmented matrix
    vector<vector<ld>> a(n, vector<ld>(m + 1));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) a[i][j] = A[i][j];
        a[i][m] = b[i];
    }

    vector<ll> where(m, -1); // pivot row for each column

    for (ll col = 0, row = 0; col < m && row < n; col++) {
        // find pivot
        ll sel = row;
        for (ll i = row; i < n; i++)
            if (fabsl(a[i][col]) > fabsl(a[sel][col])) sel = i;

        if (fabsl(a[sel][col]) < EPS) continue; // no pivot in this column

        swap(a[sel], a[row]);
        where[col] = row;

        // eliminate column
        for (ll i = 0; i < n; i++) if (i != row) {
            ld factor = a[i][col] / a[row][col];
            for (ll j = col; j <= m; j++)
                a[i][j] -= a[row][j] * factor;
        }
        row++;
    }

    // extract solution
    x.assign(m, 0);
    for (ll i = 0; i < m; i++)
        if (where[i] != -1)
            x[i] = a[where[i]][m] / a[where[i]][i];

    // check consistency
    for (ll i = 0; i < n; i++) {
        ld sum = 0;
        for (ll j = 0; j < m; j++) sum += a[i][j] * x[j];
        if (fabsl(sum - a[i][m]) > EPS) return 0; // inconsistent
    }

    for (ll i = 0; i < m; i++)
        if (where[i] == -1) return -1; // free variable -> infinitely many

    return 1; // unique solution
}

template <size_t M>
ll gauss_jordan_binary(vector<bitset<M>> &A,         // n rows, m columns
                       bitset<M>         &b,         // RHS (length n)
                       bitset<M>         &x,         // solution (length m)
                       ll                n,
                       ll                m)
{
    for (ll i = 0; i < n; i++) A[i][m] = b[i];

    vector<ll> where(m, -1);

    for (ll col = 0, row = 0; col < m && row < n; col++) {
        ll sel = -1;
        for (ll i = row; i < n; i++)
            if (A[i][col]) { sel = i; break; }
        if (sel == -1) continue;

        swap(A[sel], A[row]);
        where[col] = row;

        for (ll i = 0; i < n; i++)
            if (i != row && A[i][col]) A[i] ^= A[row];

        row++;
    }

    x.reset();
    for (ll i = 0; i < m; i++)
        if (where[i] != -1)
            x[i] = A[where[i]][m];

    for (ll i = 0; i < n; i++) {
        bool sum = 0;
        for (ll j = 0; j < m; j++) sum = sum ^ (A[i][j] & x[j]);
        if (sum != A[i][m]) return 0;
    }

    for (ll i = 0; i < m; i++)
        if (where[i] == -1) return -1;

    return 1;
}

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
