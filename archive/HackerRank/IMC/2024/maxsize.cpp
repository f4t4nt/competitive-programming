#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'maxSize' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY matrix
 *  2. INTEGER threshold
 */

bool valid(int m, int n, vector<vector<int>> &pref, int threshold) {
    for (int i = m; i <= n; i++) {
        for (int j = m; j <= n; j++) {
            if (pref[i][j] - pref[i-m][j] - pref[i][j-m] + pref[i-m][j-m] > threshold)
                return false;
        }
    }
    return true;
}

int maxSize(vector<vector<int>> matrix, int threshold) {
    int n = matrix.size();
    vector<vector<int>> pref(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] = matrix[i-1][j-1] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
        }
    }
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (valid(mid, n, pref, threshold)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
