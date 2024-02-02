#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

const ll INF = 1e18;
const ld EPS = 1e-9;

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

    ld solve(vector<ld> &x) {
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m; cin >> n >> m;
    vector<ld> total_raw(n);
    FOR (i, n) cin >> total_raw[i];
    vector<vector<ld>> percent(n, vector<ld>(m));
    vector<ld> price(m), x;
    FOR (i, m) {
        FOR (j, n) cin >> percent[j][i], percent[j][i] /= 100;
        cin >> price[i];
    }
    Simplex simplex(percent, total_raw, price);
    ld res = simplex.solve(x);
    cout << fixed << setprecision(2) << res << '\n';

    return 0;
}