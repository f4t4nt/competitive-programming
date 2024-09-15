#include <bits/stdc++.h>

using namespace std;

void solve_fib_tree(int u, int x, vector<int> &fib, string &res, char l, char r) {
    while (u != 0) {
        u--;
        if (u < fib[x]) {
            x -= 2;
            res += l;
        } else {
            u -= fib[x];
            x--;
            res += r;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n = 4, src = 4, dst = 9;
    vector<int> fib(n + 2);
    for (int i = 0; i < n; i++) fib[i + 2] = fib[i] + fib[i + 1] + 1;
    int x = n;
    while (src != 0 && dst != 0 && (src <= fib[x]) == (dst <= fib[x])) {
        src--, dst--;
        if (src < fib[x]) {
            x -= 2;
        } else {
            src -= fib[x], dst -= fib[x];
            x++;
        }
    }
    string res = "";
    solve_fib_tree(src, x, fib, res, 'U', 'U');
    solve_fib_tree(dst, x, fib, res, 'L', 'R');
    cout << res << '\n';

    return 0;
}