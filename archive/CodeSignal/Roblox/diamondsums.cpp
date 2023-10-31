#include <bits/stdc++.h>
 
using namespace std;

int get_sum(int i, int j, vector<vector<int>> matrix, int radius) {
    int len = 1, k = i - radius + 1, rv = 0;
    while (len <= radius) {
        cout << k << ':' <<  j - len + 1 << ' ' << j + len << '\n';
        for (int x = j - len + 1; x < j + len; x++) {
            rv += matrix[k][x];
        }
        k++;
        len++;
    }
    len -= 2;
    while (len > 0) {
        cout << k << ':' << j - len + 1 << ' ' << j + len << '\n';
        for (int x = j - len + 1; x < j + len; x++) {
            rv += matrix[k][x];
        }
        k++;
        len--;
    }
    return rv;
}

int solution(vector<vector<int>> matrix, int radius) {
    int rv = 0;
    for (int i = radius - 1; i < matrix.size() - radius + 1; i++) {
        for (int j = radius - 1; j < matrix[0].size() - radius + 1; j++) {
            rv = max(rv, get_sum(i, j, matrix, radius));
            cout << '\n';
        }
    }
    return rv;
}