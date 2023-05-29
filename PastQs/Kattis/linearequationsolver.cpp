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

constexpr ll INF = 1e18;
constexpr ld EPS = 1e-9;

ll gauss_jordan(vector<vector<ld>> &A, vector<ld> &b, vector<ld> &x) {
    ll n = A.size(), m = A[0].size();
    vector<vector<ld>> a(n, vector<ld>(m + 1));
    FOR(i, n) {
        FOR(j, m) {
            a[i][j] = A[i][j];
        }
        a[i][m] = b[i];
    }
    vector<ll> where(m, -1);
    for (ll col = 0, row = 0; col < m && row < n; col++) {
        ll sel = row;
        FOB (i, row, n) {
            if (abs(a[i][col]) > abs(a[sel][col])) {
                sel = i;
            }
        }
        if (abs(a[sel][col]) < EPS) {
            continue;
        }
        FOB (i, col, m + 1) {
            swap(a[sel][i], a[row][i]);
        }
        where[col] = row;
        FOR (i, n) {
            if (i != row) {
                ld c = a[i][col] / a[row][col];
                FOB (j, col, m + 1) {
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        row++;
    }
    x.assign(m, 0);
    FOR (i, m) {
        if (where[i] != -1) {
            x[i] = a[where[i]][m] / a[where[i]][i];
        }
    }
    FOR (i, n) {
        ld sum = 0;
        FOR (j, m) {
            sum += a[i][j] * x[j];
        }
        if (abs(sum - a[i][m]) > EPS) { // may need to change for modulo
            return 0;
        }
    }
    FOR (i, m) {
        if (where[i] == -1) {
            return INF;
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<vector<ld>> A(n, vector<ld>(n));
        vector<ld> b(n);
        FOR (i, n) {
            FOR (j, n) {
                cin >> A[i][j];
            }
        }
        FOR (i, n) {
            cin >> b[i];
        }
        vector<ld> x;
        ll rv = gauss_jordan(A, b, x);
        if (rv == 0) {
            cout << "inconsistent\n";
        } elif (rv == INF) {
            cout << "multiple\n";
        } else {
            FOR (i, n) {
                cout << fixed << setprecision(10) << x[i] << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}