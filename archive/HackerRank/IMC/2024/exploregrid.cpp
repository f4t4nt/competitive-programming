#include <bits/stdc++.h>
using namespace std;

// Complete the 'exploreGrid' function below.

// The function is expected to return an INTEGER.
// The function accepts following parameters:
//  1. STRING_ARRAY grid
//  2. INTEGER row_start
//  3. INTEGER column_start
//  4. INTEGER row_end
//  5. INTEGER column_end

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 0, 1};

bool in_bound(int x, int y, int n, int m) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

int exploreGrid(vector<string> grid, int row_start, int column_start, int row_end, int column_end) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> cost(n, vector<int>(m, 1e9));
    cost[row_start][column_start] = 0;
    queue<pair<int, int>> bfs;
    bfs.push({row_start, column_start});
    
    while (!bfs.empty()) {
        auto [x, y] = bfs.front();
        bfs.pop();
        int c = cost[x][y];
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k], nc = c + dc[k];
            if (in_bound(nx, ny, n, m) && grid[nx][ny] == '-' && nc < cost[nx][ny]) {
                cost[nx][ny] = nc;
                bfs.push({nx, ny});
            }
        }
    }
    
    if (cost[row_end][column_end] == 1e9) return -1;
    return cost[row_end][column_end];
}
