#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

// imma show YOU how great i am.

const ll INF = 1e18;
const ld EPS = 1e-8;

struct Simplex {
    ll m, n;
    vector<ll> N, B;
    vector<vector<ld>> D;

    // Ax <= b, max c.x with x >= 0
    Simplex(vector<vector<ld>> &A, vector<ld> &b, vector<ld> &c) :
        m(sz(b)), n(sz(c)), N(n + 1), B(m), D(m + 2, vector<ld>(n + 2)) {
        FOR (i, m) FOR (j, n) D[i][j] = A[i][j];
        FOR (i, m) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
        FOR (j, n) { N[j] = j; D[m][j] = -c[j]; }
        N[n] = -1; D[m + 1][n] = 1;
    }

    void pivot(ll r, ll s) {
        ld inv = 1 / D[r][s];
        FOR (i, m + 2) if (i != r) FOR (j, n + 2) if (j != s)
            D[i][j] -= D[r][j] * D[i][s] * inv;
        FOR (j, n + 2) if (j != s) D[r][j] *= inv;
        FOR (i, m + 2) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool simplex(ll phase) {
        ll x = m + phase - 1;
        for (;;) {
            ll s = -1;
            FOR (j, n + 1) if (N[j] != -phase) {
                if (s == -1 || make_pair(D[x][j], N[j]) <
                    make_pair(D[x][s], N[s])) s = j;
            }
            if (D[x][s] >= -EPS) return true;
            ll r = -1;
            FOR (i, m) {
                if (D[i][s] <= EPS) continue;
                if (r == -1 || make_pair(D[i][n + 1] / D[i][s], B[i]) <
                    make_pair(D[r][n + 1] / D[r][s], B[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    ll solve(vector<ld> &x) {
        ll r = 0;
        FOB (i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -EPS) {
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -EPS) return -INF;
            FOR (i, m) if (B[i] == -1) {
                ll s = 0;
                FOB (j, 1, n + 1) if (D[i][j] < D[i][s]) s = j;
                pivot(i, s);
            }
        }
        bool ok = simplex(1); x = vector<ld>(n);
        FOR (i, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return ok ? D[m][n + 1] : INF;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ld a, b, m, o;
    cin >> a >> b >> m >> o;
    // max R = ax + by
    // c = [a, b]
    // x >= 1 -> -x <= -1
    // y >= 1 -> -y <= -1
    // x + y <= m
    // 2x + y >= o, -2x - y <= -o
    // A:
    // [-1 0]
    // [0 -1]
    // [1 1]
    // [-2 -1]
    // B:
    // [-1]
    // [-1]
    // [m]
    // [-o]
    vector<vector<ld>> A = {
        {-1, 0},
        {0, -1},
        {1, 1},
        {-2, -1}
    };
    vector<ld> B = {-1, -1, m, -o};
    vector<ld> C = {a, b};
    Simplex simplex(A, B, C);
    vector<ld> x;
    ll rv = simplex.solve(x);
    cout << rv << '\n';

    return 0;
}