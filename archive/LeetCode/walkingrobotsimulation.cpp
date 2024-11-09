#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    int dx[4] = { 1, 0, -1, 0 },
        dy[4] = { 0, 1, 0, -1 };

public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        set<pair<int, int>> obstacle_set;
        for (auto &obstacle : obstacles) {
            obstacle_set.insert({obstacle[0], obstacle[1]});
        }
        int max_distance = 0,
            direction = 1,
            current_x = 0,
            current_y = 0;
        for (int &command : commands) {
            if (command < 0) {
                if (command == -2) {
                    direction = (direction + 1) % 4;
                } else if (command == -1) {
                    direction = (direction + 3) % 4;
                }
            } else {
                int steps_left = command;
                while (steps_left && !obstacle_set.count({current_x + dx[direction], current_y + dy[direction]})) {
                    current_x += dx[direction];
                    current_y += dy[direction];
                    max_distance = max(max_distance, current_x * current_x + current_y * current_y);
                    steps_left--;
                }
            }
        }
        return max_distance;
    }
};