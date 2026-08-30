#include <bits/stdc++.h>

using namespace std;

class Solution {
    using ll = long long;
    int n;
    unordered_set<ll> edges;

    ll encode(int u, int v) { return 1LL * u * (n + 1) + v; }

    bool canConnect(int u, int v) {
        return !edges.count(encode(u, v));
    }

    bool existsThird(int a, int b) {
        for (int w = 1; w <= n; w++) {
            if (w == a || w == b) continue;
            if (canConnect(a, w) && canConnect(b, w)) return true;
        }
        return false;
    }

public:
    bool isPossible(int n_, vector<vector<int>>& inputEdges) {
        n = n_;
        vector<int> degree(n + 1);
        for (auto& e : inputEdges) {
            int u = e[0], v = e[1];
            degree[u]++; degree[v]++;
            edges.insert(encode(u, v));
            edges.insert(encode(v, u));
        }

        vector<int> odd;
        for (int i = 1; i <= n; i++) if (degree[i] & 1) odd.push_back(i);

        if (odd.empty()) return true;
        if (odd.size() == 2) {
            int a = odd[0], b = odd[1];
            return canConnect(a, b) || existsThird(a, b);
        }
        if (odd.size() == 4) {
            int a = odd[0], b = odd[1], c = odd[2], d = odd[3];
            vector<array<int,4>> pairings = {
                {a,b,c,d}, {a,c,b,d}, {a,d,b,c}
            };
            for (auto& p : pairings) {
                if (canConnect(p[0], p[1]) && canConnect(p[2], p[3])) 
                    return true;
            }
            return false;
        }
        return false;
    }
};
