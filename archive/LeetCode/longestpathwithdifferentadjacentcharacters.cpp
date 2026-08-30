#include <bits/stdc++.h>

using namespace std;

class Solution {
    int ans = 0;
    string s;
    vector<vector<int>> children;

    int dfs(int v) {
        int best1 = 0, best2 = 0;
        for (int c : children[v]) {
            int len = dfs(c);
            if (s[v] == s[c]) continue;
            if (len > best1) {
                best2 = best1;
                best1 = len;
            } else if (len > best2) {
                best2 = len;
            }
        }
        ans = max(ans, best1 + best2 + 1);
        return best1 + 1;
    }

public:
    int longestPath(vector<int>& parent, string s) {
        int n = s.size();
        this->s = s;
        children.assign(n, {});
        for (int i = 1; i < n; i++) {
            children[parent[i]].push_back(i);
        }
        dfs(0);
        return ans;
    }
};
