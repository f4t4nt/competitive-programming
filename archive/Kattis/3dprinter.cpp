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

// struct Matrix {
//     vector<vector<ld>> mat;
//     ll n, m;
//     Matrix(ll n, ll m) : n(n), m(m) {
//         mat.resize(n, vector<ld>(m));
//     }
//     Matrix(vector<vector<ld>> mat) :
//         mat(mat), n(mat.size()), m(mat[0].size()) {}
//     Matrix operator*(const Matrix &other) const {
//         Matrix rv(n, other.m);
//         FOR(i, n) {
//             FOR(j, other.m) {
//                 FOR(k, m) {
//                     rv.mat[i][j] += mat[i][k] * other.mat[k][j];
//                 }
//             }
//         }
//         return rv;
//     }
//     Matrix operator^(ll p) const {
//         Matrix rv(n, n);
//         FOR(i, n) {
//             rv.mat[i][i] = 1;
//         }
//         Matrix a = *this;
//         while (p) {
//             if (p & 1) {
//                 rv = rv * a;
//             }
//             a = a * a;
//             p >>= 1;
//         }
//         return rv;
//     }
//     ld det() const {
//         Matrix a = *this;
//         ld rv = 1;
//         FOR(i, n) {
//             ll p = i;
//             FOB(j, i + 1, n) {
//                 if (abs(a.mat[j][i]) > abs(a.mat[p][i])) {
//                     p = j;
//                 }
//             }
//             if (p != i) {
//                 swap(a.mat[i], a.mat[p]);
//                 rv *= -1;
//             }
//             if (abs(a.mat[i][i]) < 1e-9) {
//                 return 0;
//             }
//             rv *= a.mat[i][i];
//             FOB(j, i + 1, n) {
//                 ld c = a.mat[j][i] / a.mat[i][i];
//                 FOB(k, i, n) {
//                     a.mat[j][k] -= c * a.mat[i][k];
//                 }
//             }
//         }
//         return rv;
//     }
// };

ld det(vector<vector<ld>> mat) {
    ld &a = mat[0][0], &b = mat[0][1], &c = mat[0][2], &d = mat[0][3],
        &e = mat[1][0], &f = mat[1][1], &g = mat[1][2], &h = mat[1][3],
        &i = mat[2][0], &j = mat[2][1], &k = mat[2][2], &l = mat[2][3],
        &m = mat[3][0], &n = mat[3][1], &o = mat[3][2], &p = mat[3][3];
    ld rv = a*(f*k*p-f*l*o-g*j*p+g*l*n+h*j*o-h*k*n)
        - b*(e*k*p-e*l*o-g*i*p+g*l*m+h*i*o-h*k*m)
        + c*(e*j*p-e*l*n-f*i*p+f*l*m+h*i*n-h*j*m)
        - d*(e*j*o-e*k*n-f*i*o+f*k*m+g*i*n-g*j*m);
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ld rv = 0;
    ll n, f, v;
    cin >> n;
    // [polygon][face][vertex][x,y,z]
    vector<vector<vector<vector<ld>>>> pts0(n);
    vector<vector<ld>> coms(n, vector<ld>(3));
    FOR (i, n) {
        cin >> f;
        pts0[i].resize(f);
        ll cnt = 0;
        FOR (j, f) {
            cin >> v;
            cnt += v;
            pts0[i][j].resize(v);
            FORE (pt, pts0[i][j]) {
                pt.resize(3);
                cin >> pt[0] >> pt[1] >> pt[2];
                coms[i][0] += pt[0];
                coms[i][1] += pt[1];
                coms[i][2] += pt[2];
            }
        }
        coms[i][0] /= cnt;
        coms[i][1] /= cnt;
        coms[i][2] /= cnt;
    }
    vector<ld> volsn, volsf, volsv;
    FOR (i, n) {
        ld voln = 0;
        FOR (j, sz(pts0[i])) {
            ld volf = 0;
            auto pts = pts0[i][j];
            // Matrix mat(4, 4);
            // // x1=pts[0][0]     x2=pts[i][0]    x3=pts[i+1][0]  x4=coms[i][0]
            // // y1=pts[0][1]     y2=pts[i][1]    y3=pts[i+1][1]  y4=coms[i][1]
            // // z1=pts[0][2]     z2=pts[i][2]    z3=pts[i+1][2]  z4=coms[i][2]
            // // 1                1               1               1
            // mat.mat[0][0] = pts[0][0];
            // mat.mat[1][0] = pts[0][1];
            // mat.mat[2][0] = pts[0][2];
            // mat.mat[3][0] = mat.mat[3][1] = mat.mat[3][2] = mat.mat[3][3] = 1;
            // mat.mat[0][3] = coms[i][0];
            // mat.mat[1][3] = coms[i][1];
            // mat.mat[2][3] = coms[i][2];
            FOB (k, 1, sz(pts) - 1) {
                // mat.mat[0][1] = pts[k][0];
                // mat.mat[1][1] = pts[k][1];
                // mat.mat[2][1] = pts[k][2];
                // mat.mat[0][2] = pts[k + 1][0];
                // mat.mat[1][2] = pts[k + 1][1];
                // mat.mat[2][2] = pts[k + 1][2];
                // ld volv = abs(mat.det() / 6);
                ld volv = abs(det({
                    {pts[0][0], pts[k][0], pts[k + 1][0], coms[i][0]},
                    {pts[0][1], pts[k][1], pts[k + 1][1], coms[i][1]},
                    {pts[0][2], pts[k][2], pts[k + 1][2], coms[i][2]},
                    {1, 1, 1, 1}
                })) / 6;
                rv += volv;
                volf += volv;
                voln += volv;
                volsv.pb(volv);
            }
            volsf.pb(volf);
        }
        volsn.pb(voln);
    }
    cout << fixed << setprecision(2) << abs(rv) << '\n';

    return 0;
}