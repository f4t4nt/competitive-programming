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

// https://www.facebook.com/codingcompetitions/hacker-cup/2022/qualification-round/problems/B1

ll dx[4] = { 0, 1, 0, -1 };
ll dy[4] = { 1, 0, -1, 0 };

// returns false if friendless tree
bool verify(vector<vector<ll>> &g, ll x, ll y, ll &r, ll &c) {
    if (x < 0 ||
        x >= r ||
        y < 0 ||
        y >= c ||
        g[x][y] <= 0) {
        return true;
    }
    ll count = 0;
    FOR(i, 4) {
        if (x + dx[i] < 0 ||
            x + dx[i] >= r ||
            y + dy[i] < 0 ||
            y + dy[i] >= c) {
            continue;
        } elif (g[x + dx[i]][y + dy[i]] > 0) {
            count++;
        }
    }
    return count > 1;
}

void clear(vector<vector<ll>> &g, ll x, ll y, ll &r, ll &c) {
    if (!verify(g, x, y, r, c) && g[x][y] == 2) {
        g[x][y] = 0;
        FOR(i, 4) {
            if (x + dx[i] < 0 ||
                x + dx[i] >= r ||
                y + dy[i] < 0 ||
                y + dy[i] >= c) {
                continue;
            }
            clear(g, x + dx[i], y + dy[i], r, c);
        }
    }
}

int main() {
    ll T;
    cin >> T;
    FOR(t, T) {
        ll r, c;
        cin >> r >> c;
        vector<vector<ll>> g(r, vector<ll>(c));
        FOR(i, r) {
            FOR(j, c) {
                char x;
                cin >> x;
                if (x == '.') g[i][j] = 2;
                elif (x == '^') g[i][j] = 1;
                else g[i][j] = -1;
            }
        }
        FOR(i, r) {
            FOR(j, c) {
                clear(g, i, j, r, c);
            }
        }
        bool valid = true;
        FOR(i, r) {
            FOR(j, c) {
                valid &= verify(g, i, j, r, c);
            }
        }
        cout << "Case #" << t + 1 << ": ";
        if (valid) {
            cout << "Possible\n";
            FOR(i, r) {
                FOR(j, c) {
                    if (g[i][j] > 0) cout << '^';
                    elif (g[i][j] == 0) cout << '.';
                    else cout << '#';
                }
                cout << '\n';
            }
        } else cout << "Impossible\n";
    }
    return 0;
}