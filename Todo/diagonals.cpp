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

int neg_one = -1;

struct Cell {
    ch val = ' '; // left slash or right slash
    vector<int*> corners = {&neg_one, &neg_one, &neg_one, &neg_one};
};

str g_to_str(vector<vector<Cell>> &g) {
    str s = "";
    FOR (i, sz(g)) {
        FOR (j, sz(g)) {
            s += g[i][j].val;
        }
        s += '\n';
    }
    return s;
}

void seed4(ll &n, vector<vector<Cell>> &g) {
    FOR (i, n) {
        FOR (j, n) {
            if (*g[i][j].corners[0] == 4 || *g[i][j].corners[3] == 4) {
                g[i][j].val = '\\';
            } elif (*g[i][j].corners[1] == 4 || *g[i][j].corners[2] == 4) {
                g[i][j].val = '/';
            }
        }
    }
    FOR (i, n) {
        FOR (j, n) {
            if (g[i][j].val == '\\') {
                *g[i][j].corners[0]--;
                *g[i][j].corners[3]--;
            } elif (g[i][j].val == '/') {
                *g[i][j].corners[1]--;
                *g[i][j].corners[2]--;
            }
        }
    }
}

void seed0(ll &n, vector<vector<Cell>> &g) {
    FOR (i, n) {
        FOR (j, n) {
            if (g[i][j].val != ' ') {
                continue;
            }
            if (*g[i][j].corners[0] == 0 || *g[i][j].corners[3] == 0) {
                g[i][j].val = '/';
                *g[i][j].corners[1] = max(-1, *g[i][j].corners[1] - 1);
                *g[i][j].corners[2] = max(-1, *g[i][j].corners[2] - 1);
            } elif (*g[i][j].corners[1] == 0 || *g[i][j].corners[2] == 0) {
                g[i][j].val = '\\';
                *g[i][j].corners[0] = max(-1, *g[i][j].corners[0] - 1);
                *g[i][j].corners[3] = max(-1, *g[i][j].corners[3] - 1);
            }
        }
    }
}

int main() {
    ll n;
    cin >> n;
    vector<vector<int>> input(n + 1, vector<int>(n + 1));
    FOR (i, n + 1) {
        FOR (j, n + 1) {
            char c;
            cin >> c;
            if (c == '+') {
                input[i][j] = -1;
            } else {
                input[i][j] = c - '0';
            }
        }
    }
    vector<vector<Cell>> g(n, vector<Cell>(n));
    FOR (i, n) {
        FOR (j, n) {
            g[i][j].corners[0] = &input[i][j];
            g[i][j].corners[1] = &input[i][j + 1];
            g[i][j].corners[2] = &input[i + 1][j];
            g[i][j].corners[3] = &input[i + 1][j + 1];
        }
    }
    seed4(n, g);
    cout << g_to_str(g) << '\n';
    FOR (i, n) {
        seed0(n, g);
        cout << g_to_str(g) << '\n';
    }
    FOR (i, n) {
        FOR (j, n) {
            cout << g[i][j].val;
        }
        cout << '\n';
    }
    return 0;
}