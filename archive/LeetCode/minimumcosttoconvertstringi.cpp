#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        const int INF = 5e8;
        vector<vector<int>> adj(26, vector<int>(26, INF));
        #pragma omp parallel for
        for (int i = 0; i < 26; ++i) {
            adj[i][i] = 0;
        }
        #pragma omp parallel for
        for (int i = 0; i < original.size(); ++i) {
            int src = original[i] - 'a';
            int dst = changed[i] - 'a';
            int dist = cost[i];
            #pragma omp critical
            {
                adj[src][dst] = min(adj[src][dst], dist);
            }
        }
        for (int k = 0; k < 26; ++k) {
            #pragma omp parallel for
            for (int i = 0; i < 26; ++i) {
                for (int j = 0; j < 26; ++j) {
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
                }
            }
        }
        long long res = 0;
        #pragma omp parallel for reduction(+:res)
        for (int i = 0; i < source.size(); ++i) {
            int src = source[i] - 'a';
            int dst = target[i] - 'a';
            int dist = adj[src][dst];
            if (dist == INF) return -1;
            res += dist;
        }
        return res;
    }
};