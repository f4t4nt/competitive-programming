#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    bool equalArr(vector<int>& arr, int prv, int i, int j) {
        for (int a = prv, b = i; a < i; a++, b++) {
            if (arr[a] != arr[b]) {
                return false;
            }
        }
        return true;
    }

public:
    bool containsPattern(vector<int>& arr, int m, int k) {
        int n = arr.size();
        vector<int> dp(n, 1);
        for (int i = m, j = 2 * m; j <= n; i++, j++) {
            int prv = i - m;
            if (equalArr(arr, prv, i, j)) {
                dp[i] = dp[prv] + 1;
                if (dp[i] >= k) {
                    return true;
                }
            }
        }
        return false;
    }
};