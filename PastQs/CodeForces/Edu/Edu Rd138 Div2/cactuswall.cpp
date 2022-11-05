#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

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

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
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

constexpr ll dx[4] = {1, 0, -1, 0};
constexpr ll dy[4] = {0, 1, 0, -1};
constexpr ll dx_diag[4] = {1, 1, -1, -1};
constexpr ll dy_diag[4] = {1, -1, 1, -1};

bool on_board(ll x, ll y, ll w, ll h) {
    return 0 <= x && x < w && 0 <= y && y < h;
}

vector<vector<pair<ll, ll>>> bfs(vector<vector<ll>> &g, ll &h, ll &w) {
    vector<vector<pair<ll, ll>>> d(w, vector<pair<ll, ll>>(h, {1e18, -1}));
    vector<vector<bool>> used(w, vector<bool>(h, false));
    queue<pair<ll, ll>> q;
    FOR (i, h) {
        d[0][i] = {g[0][i], -1};
        if (d[0][i].first != 1e18) {
            q.push({0, i});
        }
    }
    while (!q.empty()) {
        ll x = q.front().first;
        ll y = q.front().second;
        q.pop();
        used[x][y] = false;
        FOR (i, 4) {
            ll nx = x + dx_diag[i];
            ll ny = y + dy_diag[i];
            if (on_board(nx, ny, w, h) && g[nx][ny] != 1e18) {
                if (d[nx][ny].first > d[x][y].first + g[nx][ny]) {
                    d[nx][ny] = {d[x][y].first + g[nx][ny], i};
                    if (!used[nx][ny]) {
                        used[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }
    return d;
}

void print_path(vector<vector<ll>> &g, vector<vector<pair<ll, ll>>> &ref, ll &h, ll &w) {
    ll min = 1e18;
    ll min_y = -1;
    FOR(i, h) {
        if (ref[w - 1][i].first < min) {
            min = ref[w - 1][i].first;
            min_y = i;
        }
    }
    ll x = w - 1;
    ll y = min_y;
    while (x > 0) {
        g[x][y] = 0;
        ll nx = x - dx_diag[ref[x][y].second];
        ll ny = y - dy_diag[ref[x][y].second];
        x = nx;
        y = ny;
    }
    g[0][y] = 0;
    FOR (y, h) {
        FOR (x, w) {
            if (g[x][y] == 0) {
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll w, h, rv = 1e18;
        cin >> h >> w;
        vector<vector<ll>> g(w, vector<ll>(h));
        vector<vector<pair<ll, ll>>> ref;
        FOR (y, h) {
            FOR (x, w) {
                char c;
                cin >> c;
                if (c == '.') {
                    g[x][y] = 1;
                } else {
                    g[x][y] = 0;
                }
            }
        }
        FOR (x, w) {
            FOR (y, h) {
                if (g[x][y] == 0) {
                    FOR (i, 4) {
                        ll nx = x + dx[i], ny = y + dy[i];
                        if (on_board(nx, ny, w, h) && g[nx][ny] == 1) {
                            g[nx][ny] = 1e18;
                        }
                    }
                }
            }
        }
        ref = bfs(g, h, w);
        FOR (y, h) {
            rv = min(rv, ref[w - 1][y].first);
        }
        if (rv == 1e18) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            print_path(g, ref, h, w);
        }
    }
    return 0;
}