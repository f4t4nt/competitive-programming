#include "bits/stdc++.h"

using namespace std;

int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

int on_grid(int i, int j, int n, int m) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

void preview0(vector<vector<char>> &grid) {
    for (auto row : grid) {
        for (char c : row) cerr << c;
        cerr << endl;
    }
    cerr << endl;
}

void preview1(vector<vector<char>> &grid, int i, int j) {
    char c = grid[i][j];
    // assert(on_grid(i, j, grid.size(), grid[0].size()));
    if (c == '0') grid[i][j] = 'x';
    else grid[i][j] = 'X';
    for (auto row : grid) {
        for (char c : row) cerr << c;
        cerr << endl;
    }
    grid[i][j] = c;
    cerr << endl;
}

vector<vector<char>> rotate90(vector<vector<char>> &grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<char>> res(m, vector<char>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            res[j][n - i - 1] = grid[i][j];
    return res;
}

int get_dist(int i, int j, int n, int m, int dir, int indent, vector<vector<char>> &grid) {
    int dist = 0;
    while (on_grid(i, j, n, m) && grid[i][j] == '0') {
        i += di[dir];
        j += dj[dir];
        dist++;
    }
    dist--;
    if (on_grid(i, j, n, m)) dist -= indent;
    return max(dist, 0);
}

bool is_ok(int i, int j, int n, int m, int dir, int indent, vector<vector<char>> &grid) {
    int tmp = 3;
    dir = (dir + 3) % 4;
    while (tmp--) {
        if (on_grid(i + di[dir], j + dj[dir], n, m)) {
            int dist = get_dist(i, j, n, m, dir, 0, grid);
            cerr << "(i, j, dir) = (" << i << ", " << j << ", " << dir << ")" << endl;
            cerr << "dist = " << dist << endl;
            if (dist < indent) return false;
        }
        dir = (dir + 1) % 4;
    }
    return true;
}

vector<vector<char>> solution(int n, int m, int startCorner, int indent, int fullRotations) {
    if (--startCorner & 1) swap(n, m);
    vector<vector<char>> res(n, vector<char>(m, '0'));
    res[0][0] = '1';
    int fullTurns = fullRotations * 4;
    int i = 0, j = 0, dir = 0;
    preview1(res, i, j);
    while (fullTurns--) {
        if (!is_ok(i, j, n, m, dir, indent, res)) break;
        int dist = get_dist(i, j, n, m, dir, indent, res);
        cerr << dist << endl;
        while (dist--) {
            res[i][j] = '1';
            i += di[dir];
            j += dj[dir];
            preview1(res, i, j);
        }
        res[i][j] = '1';
        dir = (dir + 1) % 4;
        i += di[dir];
        j += dj[dir];
        preview1(res, i, j);
    }
    while (startCorner--) {
        res = rotate90(res);
        preview0(res);
    }
    return res;
}
