#include <bits/stdc++.h>
using namespace std;
vector<string> solution(vector<vector<string>> grid, vector<vector<int>> shots) {
    vector<string> rv;
    map<string, int> cnt;
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (grid[x][y] == ".") {
                continue;
            }
            cnt[grid[x][y]]++;
        }
    }
    for (auto &shot : shots) {
        int &x = shot[0], &y = shot[1];
        if (grid[x][y] == "#") {
            rv.push_back("Already attacked");
        } else if (grid[x][y] == ".") {
            rv.push_back("Missed");
        } else {
            string ship = grid[x][y];
            cnt[ship]--;
            if (cnt[ship] == 0) {
                rv.push_back("Ship " + ship + " sunk");
                cnt.erase(ship);
            } else {
                rv.push_back("Attacked ship " + ship);
            }
            grid[x][y] = "#";
        }
    }
    return rv;
}
