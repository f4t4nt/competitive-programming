#include "bits/stdc++.h"

using namespace std;

vector<string> split(string str) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, ',')) 
        tokens.push_back(token);
    return tokens;
}

int solution(vector<vector<string>> jobs, string output_job) {
    map<string, int> ids;
    vector<int> times, deg;
    int n = jobs.size();
    vector<vector<int>> nxt(n), prv(n);
    for (auto job : jobs) ids[job[0]] = ids.size();
    for (auto job : jobs) times.push_back(stoi(job[1]));
    for (auto job : jobs) {
        int v = ids[job[0]];
        auto prvS = split(job[2]);
        deg.push_back(prvS.size());
        for (auto req : prvS) {
            int u = ids[req];
            nxt[u].push_back(v);
            prv[v].push_back(u);
        }
    }

    auto deg0 = deg;
    vector<int> ord;
    queue<int> q;
    for (int i = 0; i < n; i++) if (deg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        for (int v : nxt[u])
            if (--deg[v] == 0)
                q.push(v);
    }

    int dst = ids[output_job];
    if (!count(ord.begin(), ord.end(), dst)) return -1;
    vector<int> dp(n, -1);
    for (int u : ord) {
        int mx = 0;
        for (int v : prv[u]) {
            // cerr << u << " has prv " << v << " with time " << times[v] << endl;
            mx = max(mx, dp[v]);
        }
        // cerr << u << "'s mx is " << mx << endl;
        dp[u] = mx + times[u];
    }
    // cerr << "ids" << endl;
    // for (auto k, v : ids) cerr << k << ": " << v << endl;
    // cerr << "times" << endl;
    // for (int t : times) cerr << t << endl;
    // cerr << endl << "deg" << endl;
    // for (int d : deg0) cerr << d << endl;
    // cerr << endl << "nxt" << endl;
    // for (int i = 0; i < n; i++) {
    //     cerr << i << ": ";
    //     for (int j : nxt[i]) cerr << j << " ";
    //     cerr << endl;
    // }
    // cerr << endl << "prv" << endl;
    // for (int i = 0; i < n; i++) {
    //     cerr << i << ": ";
    //     for (int j : prv[i]) cerr << j << " ";
    //     cerr << endl;
    // }
    // cerr << endl << "ord" << endl;
    // for (int i : ord) cerr << i << endl;
    // cerr << endl << "dp" << endl;
    // for (int i : dp) cerr << i << endl;
    // cerr << endl;

    return dp[dst];
}
