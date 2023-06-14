#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

constexpr ll MOD = 1e9 + 7;

vector<vector<ll>> mulmat(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    vector<vector<ll>> rv(sz(a), vector<ll>(sz(b[0]), 0));
    FOR (i, sz(a)) {
        FOR (j, sz(b[0])) {
            FOR (k, sz(b)) {
                rv[i][j] += a[i][k] * b[k][j];
                rv[i][j] %= MOD;
            }
        }
    }
    return rv;
}

vector<vector<ll>> powmat(vector<vector<ll>> a, ll b) {
    vector<vector<ll>> rv(sz(a), vector<ll>(sz(a), 0));
    FOR (i, sz(a)) {
        rv[i][i] = 1;
    }
    while (b) {
        if (b & 1) {
            rv = mulmat(rv, a);
        }
        a = mulmat(a, a);
        b >>= 1;
    }
    return rv;
}

bool valid(ll x) {
    ll digit = x % 10;
    x /= 10;
    while (x) {
        if (x % 10 == digit) {
            return false;
        }
        digit = x % 10;
        x /= 10;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, b;
    cin >> a >> b;
    if (a < 7) {
        ll rv = 0, hi = 1;
        FOR (i, a) {
            hi *= 10;
        }
        ll lo = hi / 10;
        FOB (i, lo, hi) {
            if (valid(i) && i % 225 == b % 225) {
                rv++;
            }
        }
        cout << rv << '\n';
        return 0;
    }
    vector<vector<ll>> matrix(90, vector<ll>(90, 0)), vec(90, vector<ll>(1, 0));
    FOB (i, 1, 10) {
        vec[(i % 9) * 10 + i][0] = 1;
    }
    FOR (i, 90) {
        ll digit1 = i % 10, sum1 = i / 10;
        FOR (j, 90) {
            ll digit2 = j % 10, sum2 = j / 10;
            if (digit1 != digit2 && (sum1 + digit2) % 9 == sum2) {
                matrix[j][i] = 1;
            }
        }
    }
    vector<vector<ll>> matrix_a = powmat(matrix, a - 3);
    vector<vector<ll>> final = mulmat(matrix_a, vec);
    FOR (i, 90) {
        ll cnt = 0, digit = i % 10, sum = i / 10;
        FOR (digit1, 10) {
            if (digit == digit1) {
                continue;
            }
            FOR (digit2, 10) {
                if (digit1 != digit2 && (digit1 * 10 + digit2) % 25 == b % 25 && (sum + digit1 + digit2) % 9 == b % 9) {
                    cnt++;
                }
            }
        }
        final[i][0] *= cnt;
        final[i][0] %= MOD;
    }
    ll rv = 0;
    FOR (i, 90) {
        rv += final[i][0];
        rv %= MOD;
    }
    cout << rv << '\n';

    return 0;
}