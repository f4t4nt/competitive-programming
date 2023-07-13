#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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

bool valid_vert(ll &r1, ll &c1, ll &r2, ll &c2, ll &n, ll &m, vector<str> &grid) {
    FOR (i, n) {
        FOR (j, m) {
            ll i1 = i, j1 = 2 * c1 - j + 1;
            if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                if (grid[i][j] == '.') {
                    return false;
                } else {
                    continue;
                }
            }
            if (grid[i][j] == grid[i1][j1]) {
                return false;
            }
        }
    }
    return true;
}

void get_vert(ll &n, ll &m, vector<str> &grid, set<tuple<ll, ll, ll, ll>> &rv) {
    FOR (i, m) {
        ll r1 = 0, c1 = i, r2 = n - 1, c2 = i;
        if (valid_vert(r1, c1, r2, c2, n, m, grid)) {
            rv.insert({r1, c1, r2, c2});
            return;
        }
    }
}

bool valid_hor(ll &r1, ll &c1, ll &r2, ll &c2, ll &n, ll &m, vector<str> &grid) {
    FOR (i, n) {
        FOR (j, m) {
            ll i1 = 2 * r1 - i + 1, j1 = j;
            if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                if (grid[i][j] == '.') {
                    return false;
                } else {
                    continue;
                }
            }
            if (grid[i][j] == grid[i1][j1]) {
                return false;
            }
        }
    }
    return true;
}

void get_hor(ll &n, ll &m, vector<str> &grid, set<tuple<ll, ll, ll, ll>> &rv) {
    FOR (i, n) {
        ll r1 = i, c1 = 0, r2 = i, c2 = m - 1;
        if (valid_hor(r1, c1, r2, c2, n, m, grid)) {
            rv.insert({r1, c1, r2, c2});
            return;
        }
    }
}

bool valid_diag1(ll &r1, ll &c1, ll &r2, ll &c2, ll &n, ll &m, vector<str> &grid) {
    ll s = r1 + c1;
    FOR (i, n) {
        FOR (j, m) {
            ll i1 = s - j, j1 = s - i;
            if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                if (grid[i][j] == '.') {
                    return false;
                } else {
                    continue;
                }
            }
            if (i == i1 && j == j1) {
                if (grid[i][j] == '.') {
                    return false;
                } else {
                    continue;
                }
            }
            if (grid[i][j] == grid[i1][j1]) {
                return false;
            }
        }
    }
    return true;
}

void get_diag1(ll &n, ll &m, vector<str> &grid, set<tuple<ll, ll, ll, ll>> &rv) {
    FOR (i, n) {
        FOR (j, m) {
            if (j != 0 && i != n - 1) {
                continue;
            }
            ll r1 = i, c1 = j, r2 = i, c2 = j;
            while (r2 >= 0 && c2 < m) {
                r2--, c2++;
            }
            r2++, c2--;
            if (valid_diag1(r1, c1, r2, c2, n, m, grid)) {
                rv.insert({r1, c1, r2, c2});
                return;
            }
        }
    }
}

bool valid_diag2(ll &r1, ll &c1, ll &r2, ll &c2, ll &n, ll &m, vector<str> &grid) {
    ll s = r1 - c1;
    FOR (i, n) {
        FOR (j, m) {
            ll i1 = s + j, j1 = i - s;
            if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                if (grid[i][j] == '.') {
                    return false;
                } else {
                    continue;
                }
            }
            if (i == i1 && j == j1) {
                if (grid[i][j] == '.') {
                    return false;
                } else {
                    continue;
                }
            }
            if (grid[i][j] == grid[i1][j1]) {
                return false;
            }
        }
    }
    return true;
}

void get_diag2(ll &n, ll &m, vector<str> &grid, set<tuple<ll, ll, ll, ll>> &rv) {
    FOR (i, n) {
        FOR (j, m) {
            if (j != 0 && i != 0) {
                continue;
            }
            ll r1 = i, c1 = j, r2 = i, c2 = j;
            while (r2 < n && c2 < m) {
                r2++, c2++;
            }
            r2--, c2--;
            if (valid_diag2(r1, c1, r2, c2, n, m, grid)) {
                rv.insert({r1, c1, r2, c2});
                return;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<str> grid(n);
    FOR (i, n) {
        cin >> grid[i];
    }
    set<tuple<ll, ll, ll, ll>> rv;
    get_vert(n, m, grid, rv);
    get_hor(n, m, grid, rv);
    get_diag1(n, m, grid, rv);
    get_diag2(n, m, grid, rv);
    auto it = rv.begin();
    cout << get<0>(*it) + 1 << ' '
        << get<1>(*it) + 1 << ' '
        << get<2>(*it) + 1 << ' '
        << get<3>(*it) + 1 << '\n';

    return 0;
}