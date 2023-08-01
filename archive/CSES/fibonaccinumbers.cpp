#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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

constexpr ll MOD = 1e9 + 7;

struct Matrix {
    vector<vector<ll>> mat;
    ll n, m;

    Matrix(ll n, ll m) : n(n), m(m) {
        mat.resize(n, vector<ll>(m));
    }

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    Matrix a(2, 2);
    a.mat = {{0, 1}, {1, 1}};
    Matrix b = a ^ n;
    cout << b.mat[0][1] << '\n';

    return 0;
}