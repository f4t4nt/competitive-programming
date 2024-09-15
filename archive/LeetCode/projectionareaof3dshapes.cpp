#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        vector<vector<bool>> xy(51, vector<bool>(51, 0)), xz = xy, yz = xy;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[i].size(); j++)
                for (int k = 0; k < grid[i][j]; k++)
        {
            xy[i][j] = xz[i][k] = yz[j][k] = 1;
        }
        int res = 0;
        for (int i = 0; i < 51; i++)
            for (int j = 0; j < 51; j++)
        {
            res += xy[i][j] + xz[i][j] + yz[i][j];
        }
        return res;
    }
};