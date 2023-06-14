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
#define sz(C) (int) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(int x = 0; x < (int) e; x++)
#define FORR(x, e) for(int x = (int) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(int x = 0; x < (int) e; x += (int) i)
#define FOBI(x, b, e, i) for(int x = (int) b; x < (int) e; x += (int) i)
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

constexpr ld EPS = 1e-9;
constexpr int INF = 1e9;
constexpr int MAXN = 1e3 + 1;

map<ch, vector<int>> hex_ref = {
    {'0', {0, 0, 0, 0}},
    {'1', {0, 0, 0, 1}},
    {'2', {0, 0, 1, 0}},
    {'3', {0, 0, 1, 1}},
    {'4', {0, 1, 0, 0}},
    {'5', {0, 1, 0, 1}},
    {'6', {0, 1, 1, 0}},
    {'7', {0, 1, 1, 1}},
    {'8', {1, 0, 0, 0}},
    {'9', {1, 0, 0, 1}},
    {'a', {1, 0, 1, 0}},
    {'b', {1, 0, 1, 1}},
    {'c', {1, 1, 0, 0}},
    {'d', {1, 1, 0, 1}},
    {'e', {1, 1, 1, 0}},
    {'f', {1, 1, 1, 1}}
};

int gauss_jordan(
    vector<bitset<MAXN>> A,
    bitset<MAXN> &b,
    bitset<MAXN> &x,
    int n,
    int m
) {
    FOR (i, n) {
        A[i][m] = b[i];
    }

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        FOB (i, row, n) {
            if (A[i][col] != 0) {
                swap(A[i], A[row]);
                break;
            }
        }
        if (A[row][col] == 0) {
            continue;
        }
        where[col] = row;
        FOR (i, n) {
            if (i != row && A[i][col] != 0) {
                A[i] ^= A[row];
            }
        }
        row++;
    }

    x = bitset<MAXN>(0);
    FOR (i, m) {
        if (where[i] != -1) {
            x[i] = A[where[i]][m] / A[where[i]][i];
        }
    }
    FOR (i, n) {
        int sum = 0;
        FOR (j, m) {
            sum += A[i][j] * x[j];
        }
        if (sum != A[i][m]) {
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

    int n, q, k;
    cin >> n >> q >> k;
    vector<bitset<MAXN>> A(4 * k, bitset<MAXN>(0));
    ch c;
    bool zero = true;
    FOR (i, n) {
        FOR (j, k) {
            cin >> c;
            FOR (x, 4) {
                A[4 * j + x][i] = hex_ref[c][x];
            }
            if (i == 0 && c != '0') {
                zero = false;
            }
        }
    }

    while (q--) {
        bitset<MAXN> b;
        FOR (i, k) {
            cin >> c;
            FOR (x, 4) {
                b[4 * i + x] = hex_ref[c][x];
            }
        }
        bitset<MAXN> x;
        int cnt = gauss_jordan(A, b, x, 4 * k, n);
        if (cnt == 0) {
            cout << -1 << '\n';
        } else {
            int rv = -1;
            FORR (i, n) {
                if (x[i] == 1) {
                    rv = i + 1;
                    break;
                }
            }
            if (rv != -1) {
                cout << rv << '\n';
            } else {
                int lo = 1, hi = n;
                while (lo < hi) {
                    int mid = (lo + hi) / 2;
                    if (gauss_jordan(A, b, x, 4 * k, mid) == INF) { 
                        hi = mid;
                    } else {
                        lo = mid + 1;
                    }
                }
                if (lo == 1 && !zero) {
                    lo = -1;
                }
                cout << lo << '\n';
            }
        }
    }

    return 0;
}