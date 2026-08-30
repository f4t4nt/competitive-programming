#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<long long> vertexDegree(n);
        for (vector<int>& road : roads) {
            vertexDegree[road[0]]++;
            vertexDegree[road[1]]++;
        }
        long long result = 0;
        sort(vertexDegree.begin(), vertexDegree.end());
        for (int i = 0; i < n; i++) {
            result += vertexDegree[i] * (i + 1);
        }
        return result;
    }
};
