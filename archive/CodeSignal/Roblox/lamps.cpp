#include <bits/stdc++.h>
 
using namespace std;

int solution(vector<vector<int>> lamps) {
    // idx, true:   new lamp starts at this idx
    // idx, false:  existing lamp ends at this idx
    vector<pair<int, bool>> events;
    for (auto &lamp : lamps) {
        events.push_back({lamp[0] - lamp[1], true});
        events.push_back({lamp[0] + lamp[1] + 1, false});
    }
    sort(events.begin(), events.end());
    int cur_lamps = 0, prev = -1e9, rv = 0;
    for (auto &event : events) {
        if (cur_lamps == 1) {
            rv += event.first - prev;
            cout << '+' << event.first - prev << '\n';
        }
        if (event.second) {
            cur_lamps++;
        } else {
            cur_lamps--;
        }
        prev = event.first;
        cout << event.first << ' ' << event.second << ' ' << cur_lamps << '\n';
    }
    return rv;
}