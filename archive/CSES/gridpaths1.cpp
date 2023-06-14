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

constexpr ll dx[4] = {1, 0, -1, 0};
constexpr ll dy[4] = {0, 1, 0, -1};

ll dfs(ll move_idx, ll x, ll y, vector<vector<bool>> &visited, str &s) {
    if (x == 1 && y == 1 && move_idx == sz(s)) {
        return 1;
    } elif (x == 1 && y == 1) {
        return 0;
    } elif (move_idx == sz(s)) {
        return 0;
    } elif (visited[x + 1][y] && visited[x - 1][y] && !visited[x][y + 1] && !visited[x][y - 1]) {
        return 0;
    } elif (visited[x][y + 1] && visited[x][y - 1] && !visited[x + 1][y] && !visited[x - 1][y]) {
        return 0;
    } elif (visited[x - 1][y + 1] && visited[x + 1][y + 1] && !visited[x][y + 1] && !visited[x + 1][y]) {
        return 0;
    } elif (visited[x - 1][y + 1] && visited[x + 1][y + 1] && !visited[x][y + 1] && !visited[x - 1][y]) {
        return 0;
    } elif (visited[x - 1][y - 1] && visited[x + 1][y - 1] && !visited[x][y - 1] && !visited[x + 1][y]) {
        return 0;
    } elif (visited[x - 1][y - 1] && visited[x + 1][y - 1] && !visited[x][y - 1] && !visited[x - 1][y]) {
        return 0;
    } elif (visited[x - 1][y - 1] && visited[x - 1][y + 1] && !visited[x - 1][y] && !visited[x][y + 1]) {
        return 0;
    }
    visited[x][y] = true;
    ll rv = 0;
    if (s[move_idx] == 'U') {
        if (!visited[x][y + 1]) {
            rv += dfs(move_idx + 1, x, y + 1, visited, s);
        } else {
            visited[x][y] = false;
            return 0;
        }
    } elif (s[move_idx] == 'D') {
        if (!visited[x][y - 1]) {
            rv += dfs(move_idx + 1, x, y - 1, visited, s);
        } else {
            visited[x][y] = false;
            return 0;
        }
    } elif (s[move_idx] == 'L') {
        if (!visited[x - 1][y]) {
            rv += dfs(move_idx + 1, x - 1, y, visited, s);
        } else {
            visited[x][y] = false;
            return 0;
        }
    } elif (s[move_idx] == 'R') {
        if (!visited[x + 1][y]) {
            rv += dfs(move_idx + 1, x + 1, y, visited, s);
        } else {
            visited[x][y] = false;
            return 0;
        }
    } else {
        FOR (i, 4) {
            if (!visited[x + dx[i]][y + dy[i]]) {
                rv += dfs(move_idx + 1, x + dx[i], y + dy[i], visited, s);
            }
        }
    }
    visited[x][y] = false;
    return rv;
}

int main() {
    str s;
    cin >> s;
    vector<vector<bool>> visited(9, vector<bool>(9, false));
    FOR (i, 9) {
        visited[i][0] = true;
        visited[0][i] = true;
        visited[i][8] = true;
        visited[8][i] = true;
    }
    cout << dfs(0, 1, 7, visited, s) << '\n';
    return 0;
}